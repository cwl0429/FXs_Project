/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 26 Oct 2021 3:48:25pm
    Author:  ChunWei

  ==============================================================================
*/

#include "AllPassFilter.h"

AllPassFilter::AllPassFilter()   
{

}
AllPassFilter::~AllPassFilter()
{

}

double AllPassFilter::calcOutput(double x)
{
    
    double output;
    double theta = juce::MathConstants<double>::pi * fc / sampleRate; //twoPi or pi?
    double cosTheta = std::cos(theta);
    output = R * R * x - 2 * R * cosTheta * delay1X + delay2X - R * R * delay2Y+ 2 * R* cosTheta*delay1Y;
    delay2Y = delay1Y;
    delay1Y = output;
    delay2X = delay1X;
    delay1X = x;
    //DBG(output);
    return output;
}
void AllPassFilter::setCutoffFrequency(double myfc)
{
    fc = myfc;
}
void AllPassFilter::setR(double myR)
{
    R = myR;
}
void AllPassFilter::reset()
{
    delay1X = 0, delay2X = 0, delay1Y = 0, delay2Y = 0;
    R = 0.8;
}