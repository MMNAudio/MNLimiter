/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MnlimiterAudioProcessorEditor::MnlimiterAudioProcessorEditor (MnlimiterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);

    addAndMakeVisible(&threshold);
    threshold.setSliderStyle(Slider::SliderStyle::Rotary);
    threshold.setTextBoxStyle(Slider::TextBoxBelow, true, 70, 20);
    threshold.setColour(Slider::textBoxOutlineColourId, Colour::Colour());
    threshold.setValue(0);
    threshold.setRange(-60.0f, 10.0f, 0.001f);
    threshold.setTextValueSuffix("dB");

    addAndMakeVisible(thresholdLabel);
    thresholdLabel.setText("Threshold", dontSendNotification);
    thresholdLabel.attachToComponent(&threshold, false);
    thresholdLabel.setJustificationType(Justification::centredTop);
    
    addAndMakeVisible(attackTime);
    attackTime.setSliderStyle(Slider::SliderStyle::Rotary);
    attackTime.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    attackTime.setColour(Slider::textBoxOutlineColourId, Colour::Colour());
    attackTime.setRange(0.0f, 10.0f, 0.001f);
    attackTime.setTextValueSuffix("s");

    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack Time", dontSendNotification);
    attackLabel.attachToComponent(&attackTime, false);
    attackLabel.setJustificationType(Justification::centredTop);
   

    addAndMakeVisible(releaseTime);
    releaseTime.setSliderStyle(Slider::SliderStyle::Rotary);
    releaseTime.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    releaseTime.setColour(Slider::textBoxOutlineColourId, Colour::Colour());
    releaseTime.setRange(0.0f, 10.0f, 0.001f);
    releaseTime.setTextValueSuffix("s");

    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release Time", dontSendNotification);
    releaseLabel.attachToComponent(&releaseTime, false);
    releaseLabel.setJustificationType(Justification::centredTop);

    threshold.onValueChange = [this] {
        processor.limiterThresh = std::pow(10, (threshold.getValue() / 20));
    };

    attackTime.onValueChange = [this] {
        processor.attackTime = 1 - (std::pow(MathConstants < float > ::euler, ((1 / processor.getSampleRate()) * -2.2f) / attackTime.getValue()));
    };

    releaseTime.onValueChange = [this] {
        processor.releaseTime = 1 - (std::pow(MathConstants < float > ::euler, ((1 / processor.getSampleRate()) * -2.2f) / releaseTime.getValue()));
    };
}

MnlimiterAudioProcessorEditor::~MnlimiterAudioProcessorEditor()
{
}

//==============================================================================
void MnlimiterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /*
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    */

    Image background = ImageCache::getFromMemory(BinaryData::TestImage_jpeg, BinaryData::TestImage_jpegSize);
    g.drawImageAt(background, 0, 0);
}

void MnlimiterAudioProcessorEditor::resized()
{
    threshold.setBounds((getWidth() / 4) * 1 + (-100), (getHeight() / 2) - 50, 100, 100);
    attackTime.setBounds((getWidth() / 4) * 2 + (-50), (getHeight() / 2) - 50, 100, 100);
    releaseTime.setBounds((getWidth() / 4) * 3 + (0), (getHeight() / 2) - 50, 100, 100);

    thresholdLabel.setBounds(getWidth() / 2, (getHeight() / 2) + 200,  100, 20);
}
