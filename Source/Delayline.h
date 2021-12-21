/*
  ==============================================================================

    Delayline.h
    Created: 6 Dec 2021 1:58:49pm
    Author:  Fan

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

template <typename SampleType>
class Delayline{
public:
	Delayline();
	~Delayline();
	void prepare(juce::dsp::ProcessSpec& spec);
	void reset();
	void fillBuffer(int channel, SampleType* channelData, SampleType bufferSize);//, SampleType delayBufferSize

	void process(juce::AudioBuffer<SampleType>& buffer) {

		bufferSize = buffer.getNumSamples();
		
		for (int channel = 0; channel < buffer.getNumChannels(); channel++) 
		{ 
			auto* channelData = buffer.getWritePointer(channel);
			fillBuffer(channel, channelData, bufferSize); //, delayBufferSize
		}

		writePosition += bufferSize;
		writePosition = fmod(writePosition,delayBufferSize);
		
	}

	SampleType* getDelaySample(int channel, SampleType delayNum);
	SampleType getWritePosition();
	SampleType getDelayBufferSize();
	const SampleType* getDelayBufferReadPointer(int channel, int readPosition);

private:
	juce::AudioBuffer<SampleType> delayBuffer;
	SampleType bufferSize;
	SampleType delayBufferSize;
	SampleType writePosition{ 0 };
	SampleType readPosition{ 0 };
	SampleType currentPosition{ 0 };
	
};