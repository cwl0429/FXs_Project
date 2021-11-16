/*
  ==============================================================================

    AweLookAndFeel.h
    Created: 15 Oct 2021 10:48:42am
    Author:  ChunWei

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AweLookAndFeel_v1 : public juce::LookAndFeel_V4
{
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        auto outline = juce::Colour(204, 204, 255); //slider.findColour(juce::Slider::rotarySliderOutlineColourId); 
        auto fill = juce::Colour(133, 91, 240); //slider.findColour (juce::Slider::rotarySliderFillColourId);
        auto buttonColor = juce::Colour(50, 62, 72);


       
        

        auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(2);
    

        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin(4.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        //const float rradius = juce::jmin(width / 2, height / 2) ;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;


        juce::Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded)); // rotary botton background

        juce::Point<float> thumbPoint(bounds.getCentreX() + (arcRadius - 10.0f) * std::cos(toAngle - juce::MathConstants<float>::halfPi),
            bounds.getCentreY() + (arcRadius - 10.0f) * std::sin(toAngle - juce::MathConstants<float>::halfPi));

        g.setColour(buttonColor);
        g.fillEllipse(rx+10, ry+10, rw-20, rw-20);

        g.setColour(fill);
        g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW); //center pin

        if (slider.isEnabled())
        {
            juce::Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }
    }
    
};