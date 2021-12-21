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
	void setNumVoices();//
	void setRate(SampleType newRate);
	void setDepth(SampleType newDepth);
	void setDryWet(SampleType newMix);
	void prepare(juce::dsp::ProcessSpec spec);
	//void update(SampleType newRate, SampleType newDepth, SampleType newMix);//
	void reset();

	//void mixWithDelayBuffer(juce::AudioBuffer<SampleType>& buffer, int channel, int readPosition, int bufferSize, SampleType delayBufferSize);

	//template <typename ProcessContext>///for type
	void process(juce::AudioBuffer<SampleType>& buffer) noexcept
	{	
		delay.process(buffer);
		
		SampleType bufferSize = buffer.getNumSamples();
		SampleType delayBufferSize = delay.getDelayBufferSize();
		auto *frequency = bufferFrequency.getWritePointer(0);
		SampleType delayNum;
		
		/*for (int i = 0; i < bufferSize; ++i) 
		{
			frequency[i] = lfo.getCurrentValue();
			
		}*/
		
		for (int channel = 0; channel < buffer.getNumChannels(); channel++)
		{
			/*auto *dBuffer = delayBuffer.getWritePointer(channel);
			for (int i = 0; i < bufferSize; ++i)
			{
				delayNum = lfo.getCurrentValue() * 100 + compensation;//set depth要另外乘以frequency
				auto *delaySample = delay.getDelaySample(channel, delayNum);//delaynum要用LFO控制, 拿到單點的sample後, 寫到新的buffer, 再與原buffer mix
				dBuffer[i] = *delaySample;
			}*/
			//buffer.addFrom(channel, 0, delayBuffer.getReadPointer(channel), bufferSize);//mix with buffer
			auto *dBuffer = delayBuffer.getWritePointer(channel);
			for (int i = 0; i < bufferSize; ++i)
			{	
				dl.pushSample(channel, buffer.getSample(channel, i));
				delayNum = lfo.getCurrentValue() * 100 + compensation;//set depth要另外乘以frequency
				dl.setDelay(delayNum);
				SampleType delaySample = dl.popSample(channel);//delaynum要用LFO控制, 拿到單點的sample後, 寫到新的buffer, 再與原buffer mix
				dBuffer[i] = delaySample;
			}
			buffer.addFrom(channel, 0, delayBuffer.getReadPointer(channel), bufferSize);

		}	
	}
	
private:
	Delayline<SampleType> delay;
	SampleType bufferSize;
	LFO<SampleType> lfo;
	juce::AudioBuffer<SampleType> bufferFrequency;//裝lfo回傳的值
	juce::AudioBuffer<SampleType> delayBuffer;
	juce::dsp::DryWetMixer<SampleType> dryWet;

	double sampleRate = 44100.0;
	SampleType rate = 1.0, depth = 0.25, mix = 0.5; //feedback = 0.0///
	
	SampleType compensation = 100;
	juce::dsp::DelayLine<SampleType, juce::dsp::DelayLineInterpolationTypes::Linear> dl;
	//int writePosition = delay.getWritePosition();
};





//mixwithdelaybuffer(buffer, channel, readposition, buffersize, delaybuffersize):
//auto* channelData = buffer.getWritePointer(channel);//?????
//auto readPosition = writePosition - (bufferSize *1.0); // 1 block of audio in the past //
//if (readPosition < 0) {
//	readPosition += delayBufferSize;
//}
//
//if (readposition + buffersize < delaybuffersize) {
//	buffer.addFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel), buffersize, 0.7f, 0.7f); // 
//}//delay.getdelaybufferreadpointer(channel, readposition)
//else {
//
//	auto numsamplestoend = delaybuffersize - readposition;
//	buffer.addFromWithRamp(channel, 0, delaysample, numsamplestoend, 0.7f, 0.7f);
//
//	auto numsamplesatstart = buffersize - numsamplestoend;
//	buffer.addFromWithRamp(channel, numsamplestoend, delay.getdelaybufferreadpointer(channel, 0), numsamplesatstart, 0.7f, 0.7f);
//
//}