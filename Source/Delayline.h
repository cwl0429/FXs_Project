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

	//template <typename ProcessContext>
	SampleType process(SampleType channel, SampleType sample, int delayNum) noexcept {//const ProcessContext& context, 

		delayBuffer.setSample(channel, writePosition[channel], sample);//size_t??
		writePosition[channel] = (writePosition[channel] + 1) % totalSize;

		auto index = (readPosition[channel] - delayNum + totalSize) % totalSize;
		auto result = delayBuffer.getSample(channel, index);

		readPosition[channel] = (readPosition[channel] + 1) % totalSize;

		return result;
	}

	/*SampleType* getDelaySample(int channel, SampleType delayNum);
	SampleType getWritePosition();
	SampleType getDelayBufferSize();
	const SampleType* getDelayBufferReadPointer(int channel, int readPosition);*/

private:
	juce::AudioBuffer<SampleType> delayBuffer;
	int totalSize = 56;//56;//max delay num of samples
	std::vector<int> writePosition, readPosition;
};