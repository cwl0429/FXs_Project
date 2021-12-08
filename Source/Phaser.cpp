/*
  ==============================================================================

    Phaser.cpp
    Created: 3 Nov 2021 2:27:41pm
    Author:  ChunWei

  ==============================================================================
*/

#include "Phaser.h"
template <typename SampleType>
Phaser<SampleType>::Phaser()
{
    
    for (auto n = 0; n < numStages; ++n)
    {
        filters.add(new AllPassFilter<SampleType>());
        //filters.getUnchecked(n)->setCutoffFrequency(1000 * (n + 1));
        
    }
    dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

template <typename SampleType>
Phaser<SampleType>::~Phaser()
{

}

template <typename SampleType>
void Phaser<SampleType>::setSpec(juce::dsp::ProcessSpec &spec)
{
    /*To Do*/
    dryWet.prepare(spec);
    auto specDown = spec;
    specDown.sampleRate /= (double)maxUpdateCounter;
    specDown.maximumBlockSize = specDown.maximumBlockSize / (int)maxUpdateCounter + 1;
    bufferFrequency.setSize(1, (int)specDown.maximumBlockSize, false, false, true);
    
    lfo.setWaveForm(LFO<SampleType>::Wave::sine);

    /*get correct sampleRate eg.48000 or 44100*/
    lfo.setSampleRate(spec.sampleRate);
    for (auto n = 0; n < numStages; ++n)
        filters.getUnchecked(n)->setSampleRate(spec.sampleRate);
    
}

template <typename SampleType>
void Phaser<SampleType>::setCentreFrequency(SampleType newCentreHz)
{
    centreFrequency = newCentreHz;
    
}

template <typename SampleType>
void Phaser<SampleType>::setRate(SampleType newRate)
{
    lfo.setFrequency(4*newRate);
}

template <typename SampleType>
void Phaser<SampleType>::setDepth(SampleType newDepth)
{
    depth = newDepth;
    for (int i = 0; i < numStages; ++i)
        filters.getUnchecked(i)->setR(depth);
    
}

template <typename SampleType>
void Phaser<SampleType>::setMix(SampleType newMix)
{
    dryWet.setWetMixProportion(newMix);
}

template <typename SampleType>
void Phaser<SampleType>::setFeedback(SampleType newFeedBack)
{
    feedBackVolume = newFeedBack;
}

/*template <typename SampleType>
void Phaser<SampleType>::setLFOwave(LFO<SampleType>::Wave newWave)
{
    lfo.setWaveForm(newWave);
}*/

template <typename SampleType>
void Phaser<SampleType>::update(SampleType newRateHz, SampleType newDepth, SampleType newCentreHz, SampleType newMix)
{
    /*To DO*/
    setCentreFrequency(newRateHz);
    setDepth(newDepth);
    //set
}

template <typename SampleType>
void Phaser<SampleType>::reset()
{
    lfo.reset();
    dryWet.reset();

    updateCounter = 0;
}

template class Phaser<float>;
template class Phaser<double>;