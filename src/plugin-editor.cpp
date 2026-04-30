#include "plugin-processor.h"
#include "plugin-editor.h"

GothicChorusEditor::GothicChorusEditor(GothicChorusProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    const auto setupSlider = [this](juce::Slider& slider, std::unique_ptr<SliderAttachment>& attachment, const juce::String& paramId)
    {
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
        addAndMakeVisible(slider);
        attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, paramId, slider);
    };

    setupSlider(rateSlider, rateAttachment, "rate");
    setupSlider(depthSlider, depthAttachment, "depth");
    setupSlider(mixSlider, mixAttachment, "mix");

    setSize(400, 200);
}

GothicChorusEditor::~GothicChorusEditor()
{
}

void GothicChorusEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    
    auto bounds = getLocalBounds();
    auto itemWidth = bounds.getWidth() / 3;
    
    g.drawFittedText("Rate", bounds.removeFromLeft(itemWidth).withHeight(40), juce::Justification::centred, 1);
    g.drawFittedText("Depth", bounds.removeFromLeft(itemWidth).withHeight(40), juce::Justification::centred, 1);
    g.drawFittedText("Mix", bounds.removeFromLeft(itemWidth).withHeight(40), juce::Justification::centred, 1);
}

void GothicChorusEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(40); // Space for labels
    
    auto itemWidth = bounds.getWidth() / 3;
    
    rateSlider.setBounds(bounds.removeFromLeft(itemWidth).reduced(10));
    depthSlider.setBounds(bounds.removeFromLeft(itemWidth).reduced(10));
    mixSlider.setBounds(bounds.removeFromLeft(itemWidth).reduced(10));
}
