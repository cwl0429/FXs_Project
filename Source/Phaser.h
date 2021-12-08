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


template<typename SampleType>
class Phaser 
{
public:
    Phaser();
    ~Phaser();
    void setRate(SampleType newRateHz);// lfo frequency
    void setDepth(SampleType newDepth);
    void setCentreFrequency(SampleType newCentreHz);
    void setMix(SampleType newMix);
    void setFeedback(SampleType newFeedback);
    void reset();
    void update(SampleType newRateHz, SampleType newDepth, SampleType newCentreHz, SampleType newMix);
    void setSpec(juce::dsp::ProcessSpec &spec);

    void process(juce::dsp::ProcessContextReplacing<SampleType>& context) noexcept
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
            auto output = input - lastOutput;
            
            if (counter == 0)
            {
                
                for (int j = 0; j < numStages; ++j)
                    filters[j]->setCutoffFrequency(frequency[k] * 2000+ centreFrequency);

                /*for (int j = 0; j < numStages; ++j)
                    filters[j]->setR(frequency[k] * 0.1 + normCentreFrequency);*/

                k++;
            }

            for (int n = 0; n < numStages; ++n)
                output = filters[n]->calcOutput(output);

            outputSamples[i] = output;
            lastOutput = output*feedBackVolume;
            counter++;
            if (counter == maxUpdateCounter)
                counter = 0;
            
        }
            
        
    
        dryWet.mixWetSamples(outputBlock);
        
    }

private:
    juce::OwnedArray<AllPassFilter<SampleType>> filters;
    juce::dsp::DryWetMixer<SampleType> dryWet;
    LFO<SampleType> lfo;
    juce::AudioBuffer<SampleType> bufferFrequency;

    SampleType sampleRate = 44100.0;

    SampleType centreFrequency = 1300.0;
    SampleType normCentreFrequency = 0.8;
    SampleType rate=1.0, depth=0.5, mix=0.5;
    SampleType lastOutput=0;
    SampleType feedBackVolume = 0.05;

    int updateCounter = 0;
    const int maxUpdateCounter = 4;
    const int numStages = 6;
};