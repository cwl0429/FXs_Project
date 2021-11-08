/*
  ==============================================================================

    LFO.cpp
    Created: 26 Oct 2021 5:59:59pm
    Author:  ChunWei

  ==============================================================================
*/

#include "LFO.h"
LFO::LFO() :waveType(Wave::sine)
{
    double theta;
    double sine;

    /*sine and square build*/

    for (int i = 0; i < 1024; ++i)
    {
        theta = juce::MathConstants<double>::twoPi* i / 1024;
        sine = std::sin(theta);
        sineWave[i] = sine;
        squareWave[i] = (sine > 0) ? 1 : -1;
    }

    /*triangle build*/
    
    for (int i = 0; i < 1024; ++i)
    {
        double slope = 1 / 256;
        
        
        if (i < 256)
        {
            triangleWave[i] = i * slope;
        }
        else if (i < 763)
        {
            triangleWave[i] = triangleWave[i - 1] - slope;
        }
        else
        {
            triangleWave[i] = triangleWave[i - 1] + slope;
        }

    }

    /*sawtooth build*/

    for (int i = 0; i < 1024; ++i)
    {
        double slope = 1 / 512;

        if (i < 512)
        {
            sawtoothWave[i] = i * slope;
        }
        else
        {
            sawtoothWave[i] = -1 + i * slope;
        }
    }
    
}

LFO::~LFO()
{

}

void LFO::setFrequency(double newFrequency)
{
    //if (newFrequency <= 20 && newFrequency > 0)
        frequency = newFrequency;
    //else
       // frequency = 5;
}

void LFO::setLevel(double newLevel)
{
    level = newLevel;
}

void LFO::setWaveForm(Wave newWaveType)
{
    waveType = newWaveType;
}

void LFO::setSampleRate(double newSampleRate)
{
    sampleRate = newSampleRate;
}

double LFO::getCurrentValue()
{
    double* output;
    int index;
    currentAngle += frequency / sampleRate;
    if (currentAngle >= 1)
        currentAngle -= 1;

  
    switch (waveType)
    {
        case Wave::sine:
            output = sineWave;
            break;
        case Wave::square:
            output = squareWave;
            break;
        case Wave::triangle:
            output = triangleWave;
            break;
        case Wave::sawtooth:
            output = sawtoothWave;
            break;
        default:
            output = sineWave;
            break;
    }
    index = std::floor(currentAngle * 1024);
    
    return output[index]*level;
}

void LFO::reset()
{
    frequency = 5, level = 0.5, currentAngle = 0;
}