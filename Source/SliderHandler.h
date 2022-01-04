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
   
    
    juce::Label title;
    juce::Slider slider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    AweLookAndFeel_v1 lnf;

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
    RotarySliderWithLabel levelSlider;
    RotarySliderWithLabel a_Slider;
    RotarySliderWithLabel d_Slider;
    //RotarySliderWithLabel s_Slider;
    RotarySliderWithLabel r_Slider;

    std::vector<RotarySliderWithLabel*> sliders{  &a_Slider, &d_Slider, &r_Slider, &levelSlider };//&s_Slider

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderHandler);
};