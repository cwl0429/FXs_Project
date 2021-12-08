/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 26 Oct 2021 3:48:25pm
    Author:  ChunWei

  ==============================================================================
*/

#include "AllPassFilter.h"
template<typename SampleType>
AllPassFilter<SampleType>::AllPassFilter()   
{

}

template<typename SampleType>
AllPassFilter<SampleType>::~AllPassFilter()
{

}

template<typename SampleType>
SampleType AllPassFilter<SampleType>::calcOutput(SampleType x)
{
    
    SampleType output;
    SampleType theta = juce::MathConstants<SampleType>::twoPi * fc / sampleRate; //twoPi or pi?
    SampleType cosTheta = std::cos(theta);
    output = R * R * x - 2 * R * cosTheta * delay1X + delay2X - R * R * delay2Y+ 2 * R * cosTheta * delay1Y;
    delay2Y = delay1Y;
    delay1Y = output;
    delay2X = delay1X;
    delay1X = x;
    //DBG(output);
    return output;
}

template<typename SampleType>
void AllPassFilter<SampleType>::setCutoffFrequency(SampleType myfc)
{
    fc = myfc;
}

template<typename SampleType>
void AllPassFilter<SampleType>::setR(SampleType myR)
{
    R = myR;
}

template<typename SampleType>
void AllPassFilter<SampleType>::setSampleRate(SampleType mySampleRate)
{
    sampleRate = mySampleRate;
}

template<typename SampleType>
void AllPassFilter<SampleType>::reset()
{
    delay1X = 0, delay2X = 0, delay1Y = 0, delay2Y = 0;
    R = 0.5;
}

template class AllPassFilter<float>;
template class AllPassFilter<double>;