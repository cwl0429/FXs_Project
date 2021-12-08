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

template<typename SampleType>
class AllPassFilter
{
public:
    AllPassFilter();

    ~AllPassFilter();

    SampleType calcOutput(SampleType input);

    void setR(SampleType myR);

    void setCutoffFrequency(SampleType myfc);

    void setSampleRate(SampleType mySampleRate);

    void reset();

private:
    SampleType delay1X=0, delay2X=0, delay1Y=0, delay2Y=0;
    
    SampleType R=0.8;
    SampleType fc=1300;
    SampleType sampleRate=44100;
};