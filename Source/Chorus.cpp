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
//void Chorus<SampleType>::setShape() {
//	lfo.setWaveForm(LFO<SampleType>::Wave::sine);//LFO­n¥i¿ï¾Ü
//}

template <typename SampleType>
void Chorus<SampleType>::setRate(SampleType newRate) {
	lfo.setFrequency(newRate); //1~20
}

template <typename SampleType>
void Chorus<SampleType>::setDepth(SampleType newDepth) {
	
	depth = newDepth;

	
}

template <typename SampleType>
void Chorus<SampleType>::setDryWet(SampleType newMix) {

	dryWet.setWetMixProportion(newMix);//UI


}

template <typename SampleType>
void Chorus<SampleType>::setFeedback(SampleType newFeedback) {

	feedback = newFeedback;

}


template <typename SampleType>
void Chorus<SampleType>::prepare(juce::dsp::ProcessSpec& spec){

	bufferFrequency.setSize(1, (int)spec.maximumBlockSize, false, false, true);//initialization
	
	delay.prepare(spec);
	dryWet.prepare(spec);

	dryWet.reset();
	//reset();

	//JUCE delay line
	/*const auto maxpossibledelay = 2000;
	dl = juce::dsp::DelayLine<SampleType, juce::dsp::DelayLineInterpolationTypes::Linear>{ static_cast<int> (maxpossibledelay) };
	dl.prepare(spec);*/
	


}


template <typename SampleType>
void Chorus<SampleType>::reset() {

	//delay.reset();
	dryWet.reset();

}
template class Chorus<float>;
template class Chorus<double>;
