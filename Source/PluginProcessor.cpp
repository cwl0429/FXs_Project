/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FXs_ProjectAudioProcessor::FXs_ProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "PARAM",
                           {/*TO DO*/
                           SliderParameter("level","Level",1,0,0.2,0.1),
                           SliderParameter("rate","Rate",20,1,5,1),
                           SliderParameter("depth","Depth",0.99,0.01,0.8,0.01),
                           SliderParameter("cutoff","Cutoff",20000,0,1300,100),
                           SliderParameter("mix","Mix",1,0,0.5,0.1),
                           std::make_unique<juce::AudioParameterChoice>("wave",
                               "Wave",
                               juce::StringArray({ "Sine","Square","Sawtooth","Triangle" }),1) })
#endif 
{
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

    mySynth.clearVoices();
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
}

FXs_ProjectAudioProcessor::~FXs_ProjectAudioProcessor()
{
}

//==============================================================================

std::unique_ptr<juce::AudioParameterFloat> FXs_ProjectAudioProcessor::SliderParameter(char* id, char* name, float max, float min, float init, float step) {
    return std::make_unique<juce::AudioParameterFloat>(id,
        name,
        juce::NormalisableRange<float>(min, max, step), init,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) {return juce::String(value); },
        [](juce::String text) { return text.getFloatValue(); });
}

const juce::String FXs_ProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FXs_ProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FXs_ProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FXs_ProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FXs_ProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FXs_ProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FXs_ProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FXs_ProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FXs_ProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void FXs_ProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FXs_ProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    mySynth.setCurrentPlaybackSampleRate(sampleRate);
    singleChannelSampleFifo.prepare(samplesPerBlock);

   /* juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();
    spec.sampleRate = sampleRate;

    phaser.prepare(spec);*/


}

void FXs_ProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FXs_ProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FXs_ProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

   
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        auto* myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i));
        myVoice->setParam(
            tree.getRawParameterValue("level")->load(),
            tree.getRawParameterValue("rate")->load(),
            tree.getRawParameterValue("depth")->load(),
            tree.getRawParameterValue("cutoff")->load(),
            tree.getRawParameterValue("mix")->load()
           
        );
        
    }

    //phaser.setCentreFrequency(2000);
    //phaser.setDepth(1);
    //phaser.setFeedback(0.5);
    //phaser.setRate(5);
    //phaser.setMix(0.5);
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    /*auto block = juce::dsp::AudioBlock<float> (buffer);
    auto context = juce::dsp::ProcessContextReplacing<float> (block);
    phaser.process(context);*/


    singleChannelSampleFifo.update(buffer);

    
}

//==============================================================================
bool FXs_ProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FXs_ProjectAudioProcessor::createEditor()
{
    return new FXs_ProjectAudioProcessorEditor (*this);
}

//==============================================================================
void FXs_ProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FXs_ProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FXs_ProjectAudioProcessor();
}
