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
        filters.add(new AllPassFilter<sampleType>());
        
    }
    dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

template <typename sampleType>
Phaser<sampleType>::~Phaser()
{

}

template <typename sampleType>
void Phaser<sampleType>::setSpec(juce::dsp::ProcessSpec spec)
{
    /*To Do*/
    dryWet.prepare(spec);
    auto specDown = spec;
    specDown.sampleRate /= (double)maxUpdateCounter;
    specDown.maximumBlockSize = specDown.maximumBlockSize / (int)maxUpdateCounter + 1;
    bufferFrequency.setSize(1, (int)specDown.maximumBlockSize, false, false, true);
    
    lfo.setWaveForm(LFO<sampleType>::Wave::sine);
    
}

template <typename sampleType>
void Phaser<sampleType>::setCentreFrequency(sampleType newCentreHz)
{
    centreFrequency = newCentreHz;
    
}

template <typename sampleType>
void Phaser<sampleType>::setRate(sampleType newRate)
{
    lfo.setSampleRate(newRate);
}

template <typename sampleType>
void Phaser<sampleType>::setDepth(sampleType newDepth)
{
    /*for (int i = 0; i < numStages; ++i)
        filters[i].setR(newDepth);*/
    depth = newDepth;
}

template <typename sampleType>
void Phaser<sampleType>::setMix(sampleType newMix)
{
    dryWet.setWetMixProportion(newMix);
}

/*template <typename sampleType>
void Phaser<sampleType>::setLFOwave(LFO<sampleType>::Wave newWave)
{
    lfo.setWaveForm(newWave);
}*/

template <typename sampleType>
void Phaser<sampleType>::reset()
{
    lfo.reset();
    dryWet.reset();

    updateCounter = 0;
}

template class Phaser<float>;
template class Phaser<double>;