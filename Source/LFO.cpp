/*
  ==============================================================================

    LFO.cpp
    Created: 26 Oct 2021 5:59:59pm
    Author:  ChunWei

  ==============================================================================
*/

#include "LFO.h"

template<typename sampleType>
LFO<sampleType>::LFO() :waveType(Wave::sine)
{
    sampleType theta;
    sampleType sine;
    sampleType slope;

    /*sine and square build*/

    for (int i = 0; i < 44100; ++i)
    {
        theta = juce::MathConstants<sampleType>::twoPi* i / 44100;
        sine = std::sin(theta);
        sineWave[i] = sine;
        squareWave[i] = (sine > 0) ? 1 : -1;
    }

    /*triangle build*/

    triangleWave[0] = 0;
    slope = 0.0000907; //slope =  1/11025
    for (int i = 1; i < 44100; ++i)
    {
        
        
        
        if (i < 11025)
        {
            
            triangleWave[i] = triangleWave[i-1] + slope;
            //DBG(triangleWave[i]);
        }
        else if (i < 33075)
        {
            triangleWave[i] = triangleWave[i - 1] - slope;
        }
        else
        {
            triangleWave[i] = triangleWave[i - 1] + slope;
        }

    }

    /*sawtooth build*/
    
    sawtoothWave[0] = 0;
    slope = 0.0000453; // slope = 1 / 22050
    for (int i = 1; i < 44100; ++i)
    {
        

        if (i < 22050)
        {
            
            sawtoothWave[i] = sawtoothWave[i-1] + slope;
        }
        else
        {
            sawtoothWave[i] = -sawtoothWave[i - 1] + slope;
        }
    }
    
}

template<typename sampleType>
LFO<sampleType>::~LFO()
{

}

template<typename sampleType>
void LFO<sampleType>::setFrequency(sampleType newFrequency)
{
    
    frequency = newFrequency;
    
}

/*template<typename sampleType>
void LFO<sampleType>::setLevel(sampleType newLevel)
{
    level = newLevel;
}*/

template<typename sampleType>
void LFO<sampleType>::setWaveForm(Wave newWaveType)
{
    waveType = newWaveType;
}

template<typename sampleType>
void LFO<sampleType>::setSampleRate(sampleType newSampleRate)
{
    sampleRate = newSampleRate;
}

template<typename sampleType>
sampleType LFO<sampleType>::getCurrentValue()
{
    sampleType* output;
    int index;
    currentAngle += (frequency / sampleRate);
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
            output = squareWave;
            break;
    }
    
    index = std::floor(currentAngle * 44100) ;
    
    return *(output+index);
}

template<typename sampleType>
void LFO<sampleType>::reset()
{
    frequency = 5, currentAngle = 0;
}

template class LFO<float>;
template class LFO<double>;