/*
  ==============================================================================

    LFO.h
    Created: 26 Oct 2021 5:59:59pm
    Author:  ChunWei

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once
class LFO
{
public:
    LFO();

    ~LFO();

    enum class Wave{sine,square,triangle,sawtooth};

    void setFrequency(double newFrequency);

    void setLevel(double newLevel);

    void setWaveForm(Wave newWaveType);

    void setSampleRate(double newSampleRate);

    void reset();

    double getCurrentValue();

private:
    double sampleRate = 44100.0;
    double frequency=1, level=0.5, currentAngle=0;
    
    double sineWave[1024];
    double squareWave[1024];
    double triangleWave[1024];
    double sawtoothWave[1024];

    Wave waveType;
};