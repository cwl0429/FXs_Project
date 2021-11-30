/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 26 Oct 2021 3:48:25pm
    Author:  ChunWei

  ==============================================================================
*/

#include "AllPassFilter.h"
template<typename sampleType>
AllPassFilter<sampleType>::AllPassFilter()   
{

}

template<typename sampleType>
AllPassFilter<sampleType>::~AllPassFilter()
{

}

template<typename sampleType>
sampleType AllPassFilter<sampleType>::calcOutput(sampleType x)
{
    
    sampleType output;
    sampleType theta = juce::MathConstants<sampleType>::twoPi * fc / sampleRate; //twoPi or pi?
    sampleType cosTheta = std::cos(theta);
    output = R * R * x - 2 * R * cosTheta * delay1X + delay2X - R * R * delay2Y+ 2 * R * cosTheta * delay1Y;
    delay2Y = delay1Y;
    delay1Y = output;
    delay2X = delay1X;
    delay1X = x;
    //DBG(output);
    return output;
}

template<typename sampleType>
void AllPassFilter<sampleType>::setCutoffFrequency(sampleType myfc)
{
    fc = myfc;
}

template<typename sampleType>
void AllPassFilter<sampleType>::setR(sampleType myR)
{
    R = myR;
}

template<typename sampleType>
void AllPassFilter<sampleType>::setSampleRate(sampleType mySampleRate)
{
    sampleRate = mySampleRate;
}

template<typename sampleType>
void AllPassFilter<sampleType>::reset()
{
    delay1X = 0, delay2X = 0, delay1Y = 0, delay2Y = 0;
    R = 0.5;
}

template class AllPassFilter<float>;
template class AllPassFilter<double>;