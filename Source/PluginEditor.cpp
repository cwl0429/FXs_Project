/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FXs_ProjectAudioProcessorEditor::FXs_ProjectAudioProcessorEditor (FXs_ProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), sliderSet(p), oscilloscope(p), spectrum(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    synthChoose.addItem("Sine", 1);
    synthChoose.addItem("Square", 2);
    synthChoose.addItem("Sawtooth", 3);
    synthChoose.addItem("Triangle", 4);
    synthChoose.setJustificationType(juce::Justification::centred);

    waveComboBoxAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wave", synthChoose));

    for (auto& comp : subComponents)
        addAndMakeVisible(comp);


    addAndMakeVisible(synthChoose);
    setSize(800, 600);
}

FXs_ProjectAudioProcessorEditor::~FXs_ProjectAudioProcessorEditor()
{
}

//==============================================================================
void FXs_ProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FXs_ProjectAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    
    juce::FlexBox headLeftBlox;
    headLeftBlox.flexDirection = juce::FlexBox::Direction::column;
    headLeftBlox.items.add(juce::FlexItem(oscilloscope).withFlex(7.0f));

    juce::FlexBox headFlexBlox;
    headFlexBlox.flexDirection = juce::FlexBox::Direction::row;

    headFlexBlox.items.add(juce::FlexItem(headLeftBlox).withFlex(1.0f));
    headFlexBlox.items.add(juce::FlexItem().withFlex(0.05f));
    headFlexBlox.items.add(juce::FlexItem(spectrum).withFlex(2.0f));


    juce::FlexBox bottomFlexBlox;
    bottomFlexBlox.flexDirection = juce::FlexBox::Direction::row;
    bottomFlexBlox.items.add(juce::FlexItem(sliderSet).withFlex(5.0f));
    bottomFlexBlox.items.add(juce::FlexItem(synthChoose).withFlex(1.0f));

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::column;
    flexBox.items.add(juce::FlexItem(headFlexBlox).withFlex(7.0f));
    flexBox.items.add(juce::FlexItem().withFlex(0.2f));
    flexBox.items.add(juce::FlexItem(bottomFlexBlox).withFlex(2.0f));

    flexBox.performLayout(area.reduced(10));
}
