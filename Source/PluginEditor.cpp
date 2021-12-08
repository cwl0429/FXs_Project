/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FXs_ProjectAudioProcessorEditor::FXs_ProjectAudioProcessorEditor (FXs_ProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), sliderSet(p)
{
   
    for (auto& comp : subComponents)
        addAndMakeVisible(comp);


    
    setSize(600, 160);
}

FXs_ProjectAudioProcessorEditor::~FXs_ProjectAudioProcessorEditor()
{
}

//==============================================================================
void FXs_ProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
   
}

void FXs_ProjectAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    
    juce::FlexBox bottomFlexBlox;
    bottomFlexBlox.flexDirection = juce::FlexBox::Direction::row;
    bottomFlexBlox.items.add(juce::FlexItem(sliderSet).withFlex(5.0f));

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::column;
    
    
    flexBox.items.add(juce::FlexItem(bottomFlexBlox).withFlex(5.0f));

    flexBox.performLayout(area.reduced(10));
}
