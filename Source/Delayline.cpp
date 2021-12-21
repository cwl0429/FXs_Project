/*
  ==============================================================================

    Delayline.cpp
    Created: 6 Dec 2021 1:58:57pm
    Author:  Fan

  ==============================================================================
*/

#include "Delayline.h"

template<typename SampleType>
Delayline<SampleType>::Delayline() 
{

}

template<typename SampleType>
Delayline<SampleType>::~Delayline()
{

}

template <typename SampleType>
void Delayline<SampleType>::prepare(juce::dsp::ProcessSpec& spec) {

	delayBufferSize = spec.maximumBlockSize * 3; // 3­¿buffer
	
	delayBuffer.setSize((int)spec.numChannels, (int)delayBufferSize,false,false,true);

	/*writePosition.resize(spec.numChannels);
	readPosition.resize(spec.numChannels);*/

	reset();

}

template <typename SampleType>
SampleType* Delayline<SampleType>::getDelaySample(int channel, SampleType delayNum) {//0~1439(480*3-1)

	SampleType delayBufferIndex = currentPosition - delayNum;
	if (delayBufferIndex < 0) {
		delayBufferIndex = (delayBufferSize - 1) + delayBufferIndex;
	}
	
	currentPosition++;
	
	if (currentPosition > (delayBufferSize - 1)) {
		currentPosition -= delayBufferSize;
	}
	//DBG(delayBufferIndex);
	return delayBuffer.getWritePointer(channel, delayBufferIndex);
	
	
}

template <typename SampleType>
void Delayline<SampleType>::fillBuffer(int channel, SampleType* channelData, SampleType bufferSize) { //, SampleType delayBufferSize

	if (delayBufferSize > bufferSize + writePosition) {
		delayBuffer.copyFrom(channel, writePosition, channelData, bufferSize); //
	}
	else {
		auto numSamplesToEnd = delayBufferSize - writePosition;
		delayBuffer.copyFrom(channel, writePosition, channelData, numSamplesToEnd);

		auto numSamplesAtStart = bufferSize - numSamplesToEnd;
		delayBuffer.copyFrom(channel, 0, (channelData+(int)numSamplesToEnd), numSamplesAtStart);
	}
	
}

template <typename SampleType>
SampleType Delayline<SampleType>::getWritePosition() {

	return writePosition;
	
}

template <typename SampleType>
SampleType Delayline<SampleType>::getDelayBufferSize() {
	return delayBufferSize;

}

template <typename SampleType>
const SampleType* Delayline<SampleType>::getDelayBufferReadPointer(int channel, int readPosition) {

	return delayBuffer.getReadPointer(channel, readPosition);

}


template <typename SampleType>
void Delayline<SampleType>::reset() {
	
	///¬Ý¤£À´JUCE¼gªº
	//delayBuffer.clear();
	
}

template class Delayline<float>;
template class Delayline<double>;