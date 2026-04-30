#pragma once

#include <JuceHeader.h>
#include "plugin-processor.h"

class GothicChorusEditor : public juce::AudioProcessorEditor
{
public:
    explicit GothicChorusEditor(GothicChorusProcessor&);
    ~GothicChorusEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GothicChorusProcessor& audioProcessor;

    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider mixSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> depthAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GothicChorusEditor)
};
