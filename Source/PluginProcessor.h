/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"
#include "FIFO.h"
//==============================================================================
/**
*/
class FXs_ProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FXs_ProjectAudioProcessor();
    ~FXs_ProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;
    std::unique_ptr<juce::AudioParameterFloat> SliderParameter(char* id, char* name, float max = 2, float min = 0, float init = 0.1f, float step = 0.02);
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    SingleChannelSampleFifo<juce::AudioBuffer<float>>& getSingleChannelSampleFifo() { return singleChannelSampleFifo; }
    juce::AudioProcessorValueTreeState tree;
private:
    //==============================================================================
    juce::Synthesiser mySynth;
    

    SingleChannelSampleFifo<juce::AudioBuffer<float>> singleChannelSampleFifo{ 0 };  //queue for waveform
    double lastSampleRate;

    juce::dsp::Phaser<float> phaser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXs_ProjectAudioProcessor)


};
