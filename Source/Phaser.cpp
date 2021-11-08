/*
  ==============================================================================

    Phaser.cpp
    Created: 3 Nov 2021 2:27:41pm
    Author:  ChunWei

  ==============================================================================
*/

#include "Phaser.h"
template <typename sampleType>
Phaser<sampleType>::Phaser()
{
    
    for (auto n = 0; n < numStages; ++n)
    {
        filters.add(new AllPassFilter());
        
    }
    dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

template <typename sampleType>
Phaser<sampleType>::~Phaser()
{

}

template <typename sampleType>
void Phaser<sampleType>::setCentreFrequency(sampleType newCentreHz)
{
    centreFrequency = newCentreHz;
}

template <typename sampleType>
void Phaser<sampleType>::setRate(sampleType newRate)
{
    rate = newRate;
}

template <typename sampleType>
void Phaser<sampleType>::setDepth(sampleType newDepth)
{
    depth = newDepth;
}

template <typename sampleType>
void Phaser<sampleType>::reset()
{
    lfo.reset();
    dryWet.reset();

    updateCounter = 0;
}