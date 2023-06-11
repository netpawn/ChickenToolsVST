/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    //Add the sliders 
    reverbSlider.setSliderStyle(juce::Slider::Rotary);
    reverbSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(reverbSlider);
    
    delaySlider.setSliderStyle(juce::Slider::Rotary);
    delaySlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(delaySlider);
    
    highPassSlider.setSliderStyle(juce::Slider::Rotary);
    highPassSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(highPassSlider);
    
    lowPassSlider.setSliderStyle(juce::Slider::Rotary);
    lowPassSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(lowPassSlider);
    
    //Add the labels for the sliders
    juce::Label reverbLabel;
    reverbLabel.setText("Reverb", juce::dontSendNotification);
    reverbLabel.attachToComponent(&reverbSlider, false);
    addAndMakeVisible(reverbLabel);

    juce::Label delayLabel;
    delayLabel.setText("Delay", juce::dontSendNotification);
    delayLabel.attachToComponent(&delaySlider, false);
    addAndMakeVisible(delayLabel);

    juce::Label highPassLabel;
    highPassLabel.setText("High Pass", juce::dontSendNotification);
    highPassLabel.attachToComponent(&highPassSlider, false);
    addAndMakeVisible(highPassLabel);

    juce::Label lowPassLabel;
    lowPassLabel.setText("Low Pass", juce::dontSendNotification);
    lowPassLabel.attachToComponent(&lowPassSlider, false);
    addAndMakeVisible(lowPassLabel);

    
    
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::green);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleEQAudioProcessorEditor::resized()
{
    const int padding = 10;
    const int sliderWidth = 100;
    const int sliderHeight = 100;
    
    const int startX = padding;
    const int startY = padding;
    
    reverbSlider.setBounds (startX, startY, sliderWidth, sliderHeight);
    delaySlider.setBounds (startX + sliderWidth + padding, startY, sliderWidth, sliderHeight);
    highPassSlider.setBounds (startX, startY + sliderHeight + padding, sliderWidth, sliderHeight);
    lowPassSlider.setBounds (startX + sliderWidth + padding, startY + sliderHeight + padding, sliderWidth, sliderHeight);
}
