/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderHandler.h"
#include "Oscilloscope.h"
#include "Spectrum.h"

//==============================================================================
/**
*/
class FXs_ProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FXs_ProjectAudioProcessorEditor (FXs_ProjectAudioProcessor&);
    ~FXs_ProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FXs_ProjectAudioProcessor& audioProcessor;

    juce::ComboBox synthChoose;
    SliderHandler sliderSet;
    Oscilloscope oscilloscope;
    Spectrum spectrum;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveComboBoxAttachment;
    std::vector<juce::Component*> subComponents{ &oscilloscope, &sliderSet ,&spectrum };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXs_ProjectAudioProcessorEditor)
};
