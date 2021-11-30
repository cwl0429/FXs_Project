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
        //filters.getUnchecked(n)->setCutoffFrequency(1000 * (n + 1));
        
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

    /*get correct sampleRate eg.48000 or 44100*/
    lfo.setSampleRate(spec.sampleRate);
    for (auto n = 0; n < numStages; ++n)
        filters.getUnchecked(n)->setSampleRate(spec.sampleRate);
    
}

template <typename sampleType>
void Phaser<sampleType>::setCentreFrequency(sampleType newCentreHz)
{
    centreFrequency = newCentreHz;
    
}

template <typename sampleType>
void Phaser<sampleType>::setRate(sampleType newRate)
{
    lfo.setFrequency(4*newRate);
}

template <typename sampleType>
void Phaser<sampleType>::setDepth(sampleType newDepth)
{
    depth = newDepth;
    for (int i = 0; i < numStages; ++i)
        filters.getUnchecked(i)->setR(depth);
    
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
void Phaser<sampleType>::update(sampleType newRateHz, sampleType newDepth, sampleType newCentreHz, sampleType newMix)
{
    /*To DO*/
    setCentreFrequency(newRateHz);
    setDepth(newDepth);
    //set
}

template <typename sampleType>
void Phaser<sampleType>::reset()
{
    lfo.reset();
    dryWet.reset();

    updateCounter = 0;
}

template class Phaser<float>;
template class Phaser<double>;