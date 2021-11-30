/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/

#include "SynthVoice.h"


SynthVoice::SynthVoice()
{
    spec.numChannels = 2;
    spec.sampleRate = getSampleRate();
    spec.maximumBlockSize = 0;
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    adsr.noteOn();
    adsrParameters.attack = 0;
    adsr.setSampleRate(getSampleRate());
    noteMidiNumber = midiNoteNumber;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    currentAngle = 0.f;
    angleIncrement = frequency / getSampleRate() * juce::MathConstants<float>::twoPi;
    tailOff = 0.0;
    isPlaying = true;

    lfo.setFrequency(frequency);
    lfo.setSampleRate(getSampleRate());
    DBG("SampleRate:"<<getSampleRate());
    lfo.setWaveForm(LFO<float>::Wave::square );
    
    
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        adsr.noteOff();
    }
    else
    {
        clearCurrentNote();
        level = 0;
        currentAngle = 0.f;
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    // handle pitch wheel moved midi event
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    // handle midi control change
}

void SynthVoice::renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
    float value;
    float proportion;

    /*set Phaser*/
    if (spec.maximumBlockSize == 0)
    {
        spec.maximumBlockSize = outputBuffer.getNumSamples();
        phaser[0].setSpec(spec);
        phaser[1].setSpec(spec);
    }
    
    if (isPlaying)
    {
        adsr.setParameters(adsrParameters);
        for (int i = startSample; i < (startSample + numSamples); i++)
        {
            float adsrValue = adsr.getNextSample();
            if (adsrValue <= 0.005)
            {
                isPlaying = false;
            }
      
            value = lfo.getCurrentValue() * level;

           /*for (int i = 0; i < 4; ++i)
                value = AP[i].calcOutput(value);*/

            outputBuffer.addSample(0, i, value);
            outputBuffer.addSample(1, i, value);
            
            
            currentAngle += angleIncrement;
            if (currentAngle >= juce::MathConstants<float>::twoPi)
            {
                currentAngle -= juce::MathConstants<float>::twoPi;
            }
        }

        juce::dsp::AudioBlock<float> block(outputBuffer);

        juce::dsp::ProcessContextReplacing<float> leftChannel(block.getSingleChannelBlock(0));
        juce::dsp::ProcessContextReplacing<float> rightChannel(block.getSingleChannelBlock(1));

        /*Go through Phaser*/
        phaser[0].process(leftChannel);
        phaser[1].process(rightChannel);
        
    }
 
}




void SynthVoice::setChannel(int newChannel)
{
    channel = newChannel;
}

void SynthVoice::setParam(float newLevel, float newRate, float newDepth, float newCutoff, float newMix)
{
    level = newLevel;
    for (int i = 0; i < 2; ++i)
    {
        phaser[i].setRate(newRate);
        phaser[i].setDepth(newDepth);
        phaser[i].setCentreFrequency(newCutoff);
        phaser[i].setMix(newMix);
    }
    
}