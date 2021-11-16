/*
  ==============================================================================

    Phaser.h
    Created: 3 Nov 2021 2:27:41pm
    Author:  ChunWei

  ==============================================================================
*/
#include "JuceHeader.h"
#include "AllPassFilter.h"
#include "LFO.h"


template<typename sampleType>
class Phaser 
{
public:
    Phaser();
    ~Phaser();
    void setRate(sampleType newRateHz);
    void setDepth(sampleType newDepth);
    void setCentreFrequency(sampleType newCentreHz);
    void setMix(sampleType newMix);
    //void setLFOwave(LFO<sampleType>::Wave newWave);
    void reset();
    void update();
    void setSpec(juce::dsp::ProcessSpec spec);

    void process(juce::dsp::ProcessContextReplacing<sampleType>& context) noexcept
    {
       
       
        
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        

        const auto numChannels = 1;
        const auto numSamples = context.getInputBlock().getNumSamples();
        
        /*LFO and cutoffFrequency setting*/
        int numSamplesForLFO = 0;
        auto counter = updateCounter;

        for (int i = 0; i < numSamples; ++i)
        {
            if (counter == 0)
                numSamplesForLFO++;
            counter++;

            if (counter == maxUpdateCounter)
                counter = 0;
        }
  
        auto *frequency= bufferFrequency.getWritePointer(0);
        for (int i = 0; i < numSamplesForLFO; ++i)
        {
            frequency[i] = lfo.getCurrentValue();
        }
        
        /*sample process*/
        
        dryWet.pushDrySamples(inputBlock);
       
            
        const auto* inputSamples = inputBlock.getChannelPointer(0);
        auto* outputSamples = outputBlock.getChannelPointer(0);
        int k = 0;
        for (int i = 0; i < numSamples; ++i)
        {

            auto input = inputSamples[i];
            auto output = input-lastOutput;
            //DBG("Dry sample value " << input);
            if (counter == 0)
            {

                for (int j = 0; j < numStages; ++j)
                    filters[j]->setCutoffFrequency(frequency[k] * 4000);

                k++;
            }

            for (int n = 0; n < numStages; ++n)
                output = filters[n]->calcOutput(output);

            outputSamples[i] = output;
            lastOutput = output*feedBackVolume;
            counter++;
            if (counter == maxUpdateCounter)
                counter = 0;
            //DBG("Wet sample value "<<output);
        }
            
        
    
        dryWet.mixWetSamples(outputBlock);
        
    }

private:
    juce::OwnedArray<AllPassFilter<sampleType>> filters;
    juce::dsp::DryWetMixer<sampleType> dryWet;
    LFO<sampleType> lfo;
    juce::AudioBuffer<sampleType> bufferFrequency;

    sampleType sampleRate = 44100.0;

    sampleType centreFrequency = 1300.0;
    sampleType normCentreFrequency = 0.5;
    sampleType rate=1.0, depth=0.5, mix=0.5;
    sampleType lastOutput=0;
    sampleType feedBackVolume = 0.05;

    int updateCounter = 0;
    const int maxUpdateCounter = 4;
    const int numStages = 6;
};