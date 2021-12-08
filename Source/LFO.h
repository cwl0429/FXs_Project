/*
  ==============================================================================

    LFO.h
    Created: 26 Oct 2021 5:59:59pm
    Author:  ChunWei

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

template<typename SampleType>
class LFO
{
public:
    LFO();

    ~LFO();

    enum class Wave { sine, square, triangle, sawtooth };

    void setFrequency(SampleType newFrequency);

    //void setLevel(SampleType newLevel);

    void setWaveForm(Wave newWaveType);

    void setSampleRate(SampleType newSampleRate);

    void reset();

    SampleType getCurrentValue();

private:
    SampleType sampleRate = 44100;
    SampleType frequency = 1, currentAngle = 0;

    SampleType sineWave[44100];
    SampleType squareWave[44100];
    SampleType triangleWave[44100];
    SampleType sawtoothWave[44100];

    Wave waveType;
};