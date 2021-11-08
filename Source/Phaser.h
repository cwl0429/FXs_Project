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
    void reset();
    void update();
    

    void process(juce::AudioBuffer <sampleType>& inputBuffer) noexcept
    {
        /*get blocks*/
        //const auto& inputBlock = context.getInputBlock();
        //auto& outputBlock = context.getOutputBlock();
        //const auto numChannels = outputBlock.getNumChannels();
        //const auto numSamples = outputBlock.getNumSamples();
        // 
     
        const auto& inputBlock = inputBuffer;
        auto& outputBlock = inputBuffer;
        const auto numChannels = inputBuffer.getNumChannels();
        const auto numSamples = inputBuffer.getNumSamples();
        
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
        sampleType *frequency= new sampleType(numSamplesForLFO);
        for (int i = 0; i < numSamplesForLFO; ++i)
        {
            frequency[i] = lfo.getCurrentValue()*100;
        }
        
        /*sample process*/
        dryWet.pushDrySamples(inputBlock);
        
        for (int channel = 0; channel < numChannels; ++channel)
        {
            const auto* inputSamples = inputBlock.getReadPointer(channel);
            auto* outputSamples = outputBlock.getWritePointer(channel);
            int k = 0;
            for (int i = 0; i < numSamples; ++i)
            {
                auto input = inputSamples[i];
                auto output = input;

                if (counter == 0)
                {
                    for (int j = 0; j < numStages; ++j)
                        filters[j]->setCutoffFrequency(frequency[k]);

                    k++;
                }

                for (int n = 0; n < numStages; ++n)
                    output = filters[n]->calcOutput(output);

                outputSamples[i] = output;

                counter++;
                if (counter == maxUpdateCounter)
                    counter = 0;
        
            }
        }


        dryWet.mixWetSamples(outputBlock);
    }

private:
    juce::OwnedArray<AllPassFilter> filters;
    juce::dsp::DryWetMixer<sampleType> dryWet;
    LFO lfo;
    sampleType sampleRate = 44100.0;

    sampleType centreFrequency = 1300.0;
    sampleType normCentreFrequency = 0.5;
    sampleType rate=1.0, depth=0.5, mix=0.5;

    int updateCounter = 0;
    const int maxUpdateCounter = 4;
    const int numStages = 6;
};