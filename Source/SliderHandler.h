/*
  ==============================================================================

    SliderHandler.h
    Created: 13 Oct 2021 2:53:39pm
    Author:  ChunWei

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include "PluginProcessor.h"
#include "AweLookAndFeel_v1.h"

class RotarySliderWithLabel : public juce::Component
{
public:
    RotarySliderWithLabel(FXs_ProjectAudioProcessor& audioProcessor, juce::String titleName, juce::String unit);
    ~RotarySliderWithLabel();

    void paint(juce::Graphics&)override;
    void resized() override;

private:
    FXs_ProjectAudioProcessor& processor;

    AweLookAndFeel_v1 lnf;
    
    juce::Label title;
    juce::Slider slider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
   

};
class SliderHandler : public juce::Component
{
public:
    SliderHandler(FXs_ProjectAudioProcessor& );
    ~SliderHandler() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    FXs_ProjectAudioProcessor& processor;
    
    RotarySliderWithLabel rate_Slider;
    RotarySliderWithLabel depth_Slider;
    RotarySliderWithLabel cutoff_Slider;
    RotarySliderWithLabel mix_Slider;
    RotarySliderWithLabel feedback_Slider;

    std::vector<RotarySliderWithLabel*> sliders{ &feedback_Slider, &rate_Slider, &depth_Slider, &cutoff_Slider, &mix_Slider };

    
};