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

	delayBuffer.setSize((int)spec.numChannels, totalSize, false, false, true);
	
	writePosition.resize(spec.numChannels);
	readPosition.resize(spec.numChannels);

	for (auto vec : { &writePosition, &readPosition })
		std::fill(vec->begin(), vec->end(), 0);

	delayBuffer.clear();

	/*writePosition.resize(spec.numChannels);
	readPosition.resize(spec.numChannels);*/
}



template <typename SampleType>
void Delayline<SampleType>::reset() {
	
	
}

template class Delayline<float>;
template class Delayline<double>;