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

class AllPassFilter
{
public:
    AllPassFilter();

    ~AllPassFilter();

    double calcOutput(double input);

    void setR(double myR);

    void setCutoffFrequency(double myfc);

    void reset();

private:
    double delay1X=0, delay2X=0, delay1Y=0, delay2Y=0;
    
    double R=0.8;
    double fc=1300;
    double sampleRate=44100;
};