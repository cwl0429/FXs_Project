/*
  ==============================================================================

    LFO.h
    Created: 26 Oct 2021 5:59:59pm
    Author:  ChunWei

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

template<typename sampleType>
class LFO
{
public:
    LFO();

    ~LFO();

    enum class Wave { sine, square, triangle, sawtooth };

    void setFrequency(sampleType newFrequency);

    //void setLevel(sampleType newLevel);

    void setWaveForm(Wave newWaveType);

    void setSampleRate(sampleType newSampleRate);

    void reset();

    sampleType getCurrentValue();

private:
    sampleType sampleRate = 44100.0;
    sampleType frequency = 1, currentAngle = 0;

    sampleType sineWave[44100];
    sampleType squareWave[44100];
    sampleType triangleWave[44100];
    sampleType sawtoothWave[44100];

    Wave waveType;
};