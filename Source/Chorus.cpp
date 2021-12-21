/*
  ==============================================================================

    Chorus.cpp
    Created: 6 Dec 2021 2:45:35pm
    Author:  Fan

  ==============================================================================
*/

#include "Chorus.h"

template <typename SampleType>
Chorus<SampleType>::Chorus() {

	dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}


template <typename SampleType>
Chorus<SampleType>::~Chorus()
{
}


//template <typename SampleType>
//void Chorus<SampleType>::mixWithDelayBuffer(juce::AudioBuffer<SampleType>& buffer, int channel, int readPosition, int bufferSize, SampleType delayBufferSize){
//
//	
//}

//template <typename SampleType>
//void Chorus<SampleType>::setShape() {
//	lfo.setWaveForm(LFO<SampleType>::Wave::sine);//LFO要可選擇
//}

template <typename SampleType>
void Chorus<SampleType>::setRate(SampleType newRate) {
	lfo.setFrequency(newRate); //UI
}

template <typename SampleType>
void Chorus<SampleType>::setDepth(SampleType newDepth) {
	//寫死
}

template <typename SampleType>
void Chorus<SampleType>::setDryWet(SampleType newMix) {

	dryWet.setWetMixProportion(newMix);//UI


}

template <typename SampleType>
void Chorus<SampleType>::prepare(juce::dsp::ProcessSpec spec){

	bufferFrequency.setSize(1, (int)spec.maximumBlockSize, false, false, true);//initialization
	delayBuffer.setSize(2, (int)spec.maximumBlockSize, false, false, true);//initialization
	delay.prepare(spec);
	dryWet.prepare(spec);
	const auto maxPossibleDelay = 2000;
	dl = juce::dsp::DelayLine<SampleType, juce::dsp::DelayLineInterpolationTypes::Linear>{ static_cast<int> (maxPossibleDelay) };
	dl.prepare(spec);
	

	//reset();

}


//template <typename SampleType>
//void Chorus<SampleType>::update(SampleType newRate, SampleType newDepth, SampleType newMix) {
//
//	setShape();//
//	setRate(newRate);
//	setDepth(newDepth);
//	setDryWet(newMix);
//
//}

template <typename SampleType>
void Chorus<SampleType>::reset() {

	delay.reset();
	dryWet.reset();


}
template class Chorus<float>;
template class Chorus<double>;
