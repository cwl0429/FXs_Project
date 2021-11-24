/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <fstream> 
#include <iostream>
#include <string>
#include "SynthSound.h"
#include "LFO.h"
#include "AllPassFilter.h" 
#include "Phaser.h"
class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    SynthVoice();

    bool canPlaySound (juce::SynthesiserSound* sound) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;

    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
   
    void renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override;
    
    void setChannel(int newChannel);

    void setParam(float newLevel,float newRate, float newDepth, float newCutoff, float newMix);
    

    
private:
    float level=0.5f;
    int channel=0;
    float frequency=0;
    int noteMidiNumber=0;
    float currentAngle=0;
    float angleIncrement=0;
    float tailOff=0;
    bool isPlaying = false;
    juce::dsp::ProcessSpec spec;
    

    LFO<float> lfo;
    AllPassFilter<float> AP[4];
    Phaser<float> phaser[2];

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;
};
