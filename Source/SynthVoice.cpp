/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/

#include "SynthVoice.h"




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
    lfo.setWaveForm(LFO::Wave::square);
    //DBG(getSampleRate());
    //DBG(frequency);
    //DBG(level);
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
      
            //DBG("------");
            //DBG(currentAngle);
            //std::cout << value << std::endl;
            /*To do*/
            level = 0.5f; 

            value = lfo.getCurrentValue() * level;
            
            
            outputBuffer.addSample(0, i, value);
            outputBuffer.addSample(1, i, value);
            
            
            currentAngle += angleIncrement;
            if (currentAngle >= juce::MathConstants<float>::twoPi)
            {
                currentAngle -= juce::MathConstants<float>::twoPi;
            }
        }
        phaser.process(outputBuffer);
    }
 
}



void SynthVoice::setLevel(float newLevel)
{
    level = newLevel;
}

void SynthVoice::setChannel(int newChannel)
{
    channel = newChannel;
}

void SynthVoice::setADSR(float attack, float decay, float sustain, float release) //unit is second
{
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;
}
