/*
  ==============================================================================

    AllPassFilter.h
    Created: 26 Oct 2021 3:48:25pm
    Author:  ChunWei

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include <vector>

template<typename sampleType>
class AllPassFilter
{
public:
    AllPassFilter();

    ~AllPassFilter();

    sampleType calcOutput(sampleType input);

    void setR(sampleType myR);

    void setCutoffFrequency(sampleType myfc);

    void setSampleRate(sampleType mySampleRate);

    void reset();

private:
    sampleType delay1X=0, delay2X=0, delay1Y=0, delay2Y=0;
    
    sampleType R=0.8;
    sampleType fc=1300;
    sampleType sampleRate=44100;
};