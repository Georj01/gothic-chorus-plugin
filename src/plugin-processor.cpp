#include "plugin-processor.h"
#include "plugin-editor.h"

GothicChorusProcessor::GothicChorusProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

GothicChorusProcessor::~GothicChorusProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout GothicChorusProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"rate", 1}, "Rate", juce::NormalisableRange<float>(0.1f, 10.0f, 0.01f), 1.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"depth", 1}, "Depth", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.4f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"mix", 1}, "Mix", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    return {params.begin(), params.end()};
}

void GothicChorusProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(getTotalNumOutputChannels());

    chorus.prepare(spec);
    chorus.reset();
}

void GothicChorusProcessor::releaseResources()
{
}

void GothicChorusProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    if (buffer.getNumSamples() == 0 || buffer.getNumChannels() == 0)
        return;

    const float rate = apvts.getRawParameterValue("rate")->load();
    const float depth = apvts.getRawParameterValue("depth")->load();
    const float mix = apvts.getRawParameterValue("mix")->load();

    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setMix(mix);

    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    chorus.process(context);
}

bool GothicChorusProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* GothicChorusProcessor::createEditor()
{
    return new GothicChorusEditor(*this);
}

void GothicChorusProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void GothicChorusProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName(apvts.state.getType()))
    {
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

const juce::String GothicChorusProcessor::getName() const { return JucePlugin_Name; }
bool GothicChorusProcessor::acceptsMidi() const { return false; }
bool GothicChorusProcessor::producesMidi() const { return false; }
bool GothicChorusProcessor::isMidiEffect() const { return false; }
double GothicChorusProcessor::getTailLengthSeconds() const { return 0.0; }
int GothicChorusProcessor::getNumPrograms() { return 1; }
int GothicChorusProcessor::getCurrentProgram() { return 0; }
void GothicChorusProcessor::setCurrentProgram(int /*index*/) {}
const juce::String GothicChorusProcessor::getProgramName(int /*index*/) { return {}; }
void GothicChorusProcessor::changeProgramName(int /*index*/, const juce::String& /*newName*/) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GothicChorusProcessor();
}
