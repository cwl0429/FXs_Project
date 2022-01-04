/*
  ==============================================================================

    Chorus.h
    Created: 6 Dec 2021 2:45:24pm
    Author:  Fan

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Delayline.cpp"
#include "LFO.h"


template <typename SampleType>
class Chorus {

public:
	Chorus();
	~Chorus();
	//void setShape();
	//void setNumVoices();
	void setRate(SampleType newRate);
	void setDepth(SampleType newDepth);
	void setDryWet(SampleType newMix);
	void setFeedback(SampleType newFeedback);
	void prepare(juce::dsp::ProcessSpec& spec);
	void reset();


	template <typename ProcessContext>///for type
	void process(const ProcessContext& context) noexcept//per block
	{	
		
		const auto& inputBlock = context.getInputBlock();
		auto& outputBlock = context.getOutputBlock();

		SampleType bufferSize = inputBlock.getNumSamples();
		auto *frequency = bufferFrequency.getWritePointer(0);
		SampleType delayNum;
		
		for (int i = 0; i < bufferSize; ++i) 
		{
			frequency[i] = int(lfo.getCurrentValue() * depth * 26 + centerDelay); //lfo.getCurrentValue() * depth * 10 + centerDelay;//1~-1 map to 4~56 num samples (1~25ms)
		}

		SampleType lastOutput=0;
		dryWet.pushDrySamples(inputBlock);
		for (int channel = 0; channel < inputBlock.getNumChannels(); channel++)
		{
	
			auto* inputSamples = inputBlock.getChannelPointer(channel);
			auto* outputSamples = outputBlock.getChannelPointer(channel);

			for (int i = 0; i < bufferSize; ++i)
			{	
				auto input = inputSamples[i];
				auto output = input + lastOutput;

				delayNum = frequency[i];
				outputSamples[i] = delay.process(channel, output, delayNum);

				//JUCE delay line
				/*dl.pushSample(channel, input);
				delayNum = frequency[i];
				dl.setDelay(delayNum);
				outputSamples[i]= dl.popSample(channel);*/

				lastOutput = outputSamples[i] * feedback;
			}

		}	
		dryWet.mixWetSamples(outputBlock);
	}
	
private:
	Delayline<SampleType> delay;
	LFO<SampleType> lfo;
	juce::AudioBuffer<SampleType> bufferFrequency;//裝lfo回傳的值
	juce::dsp::DryWetMixer<SampleType> dryWet;

	//double sampleRate = 44100.0;
	SampleType rate = 1.0, depth = 0.25, mix = 0.5, feedback = 1; //feedback = 0.0///
	SampleType centerDelay = 30;

	//JUCE
	juce::dsp::DelayLine<SampleType, juce::dsp::DelayLineInterpolationTypes::Linear> dl;

};

