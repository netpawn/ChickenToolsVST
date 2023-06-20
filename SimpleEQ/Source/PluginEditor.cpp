#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_extra/juce_gui_extra.h>


//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 200);
    
    
    //Add the sliders
    reverbSlider.setSliderStyle(juce::Slider::Rotary);
    reverbSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    reverbSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    reverbSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00000000));
    reverbSlider.setRange(0.0, 10.0, 0.1); // Set range with step size of 0.1
    reverbSlider.setValue(audioProcessor.getRoomSize()); // Set default value
    reverbSlider.setTextValueSuffix(" Reverb");
    addAndMakeVisible(reverbSlider);
    // Create the AudioProcessorValueTreeState object
    audioProcessorValueTreeState = std::make_unique<juce::AudioProcessorValueTreeState>(audioProcessor, nullptr);

        // Attach the reverb slider to the "Reverb" parameter
    reverbSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*audioProcessorValueTreeState, "Reverb", reverbSlider);

        // Add the audio processor as a listener to the AudioProcessorValueTreeState
    audioProcessorValueTreeState->addParameterListener("Reverb", &audioProcessor);

    
    
    delaySlider.setSliderStyle(juce::Slider::Rotary);
    delaySlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    delaySlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    delaySlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00000000));
    delaySlider.setRange(0.0, 10.0, 0.1); // Set range with step size of 0.1
    reverbSlider.setValue(audioProcessor.getDamping());
    delaySlider.setTextValueSuffix(" Delay");
    addAndMakeVisible(delaySlider);
    
    lowPassSlider.setSliderStyle(juce::Slider::Rotary);
    lowPassSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    lowPassSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    lowPassSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00000000));
    lowPassSlider.setRange(0.0, 10.0, 0.1); // Set range with step size of 0.1
    reverbSlider.setValue(audioProcessor.getWetLevel());
    lowPassSlider.setTextValueSuffix(" LowPass");
    addAndMakeVisible(highPassSlider);
    
    highPassSlider.setSliderStyle(juce::Slider::Rotary);
    highPassSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    highPassSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    highPassSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00000000));
    highPassSlider.setRange(0.0, 10.0, 0.1); // Set range with step size of 0.1
    reverbSlider.setValue(audioProcessor.getDryLevel());
    highPassSlider.setTextValueSuffix(" HighPass");
    addAndMakeVisible(lowPassSlider);
    
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    gainSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00000000));
    gainSlider.setRange(0.0, 10.0, 0.1); // Set range with step size of 0.1
    reverbSlider.setValue(audioProcessor.getWidth());
    gainSlider.setTextValueSuffix(" Gain");
    addAndMakeVisible(gainSlider);

    freqSlider.setSliderStyle(juce::Slider::Rotary);
    freqSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    freqSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    freqSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00000000));
    freqSlider.setRange(0.0, 10.0, 0.1); // Set range with step size of 0.1
    freqSlider.setValue(0.0); // Set default value
    freqSlider.setTextValueSuffix(" Frequency");
    addAndMakeVisible(freqSlider);
        

    
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

    
    ///TEXT
    textLabel1.setText("ChickenTools VST", juce::dontSendNotification);
    textLabel1.setFont(juce::Font(20.0f)); // Set the font size for text line 1

    textLabel2.setText("made with love by @netpawn", juce::dontSendNotification);
    textLabel2.setFont(juce::Font(15.0f)); // Set the font size for text line 2

    addAndMakeVisible(textLabel1);
    addAndMakeVisible(textLabel2);
    
    
    //positioning the UI
    juce::Rectangle<int> reverbBounds = reverbSlider.getBounds();
    int reverbX = reverbBounds.getX();
    int reverbY = reverbBounds.getY();
    int reverbRight = reverbBounds.getRight();
    int reverbBottom = reverbBounds.getBottom();

    juce::Rectangle<int> delayBounds = delaySlider.getBounds();
    int delayX = delayBounds.getX();
    int delayY = delayBounds.getY();
    int delayRight = delayBounds.getRight();
    int delayBottom = delayBounds.getBottom();
    juce::Rectangle<int> lowPassBounds = lowPassSlider.getBounds();
    int lowPassX = lowPassBounds.getX();
    int lowPassY = lowPassBounds.getY();
    int lowPassRight = lowPassBounds.getRight();
    int lowPassBottom = lowPassBounds.getBottom();

    juce::Rectangle<int> highPassBounds = highPassSlider.getBounds();
    int highPassX = highPassBounds.getX();
    int highPassY = highPassBounds.getY();
    int highPassRight = highPassBounds.getRight();
    int highPassBottom = highPassBounds.getBottom();

    juce::Rectangle<int> gainBounds = gainSlider.getBounds();
    int gainX = gainBounds.getX();
    int gainY = gainBounds.getY();
    int gainRight = gainBounds.getRight();
    int gainBottom = gainBounds.getBottom();

    juce::Rectangle<int> filterBounds = freqSlider.getBounds();
    int filterX = filterBounds.getX();
    int filterY = filterBounds.getY();
    int filterRight = filterBounds.getRight();
    int filterBottom = filterBounds.getBottom();


    // Repeat the same for other sliders...

    // Print the coordinates
    std::cout << "Reverb: X = " << reverbX << ", Y = " << reverbY << ", Right = " << reverbRight << ", Bottom = " << reverbBottom << std::endl;
    std::cout << "Delay: X = " << delayX << ", Y = " << delayY << ", Right = " << delayRight << ", Bottom = " << delayBottom << std::endl;
    // Print coordinates for other sliders...
    std::cout << "Low Pass: X = " << lowPassX << ", Y = " << lowPassY << ", Right = " << lowPassRight << ", Bottom = " << lowPassBottom << std::endl;
    std::cout << "High Pass: X = " << highPassX << ", Y = " << highPassY << ", Right = " << highPassRight << ", Bottom = " << highPassBottom << std::endl;
    std::cout << "Gain: X = " << gainX << ", Y = " << gainY << ", Right = " << gainRight << ", Bottom = " << gainBottom << std::endl;
    std::cout << "Filter: X = " << filterX << ", Y = " << filterY << ", Right = " << filterRight << ", Bottom = " << filterBottom << std::endl;
    
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::grey);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    
}

void SimpleEQAudioProcessorEditor::resized()
{
    const int padding = 10;
    const int sliderWidth = 100;
    const int sliderHeight = 100;

    const int startX = ((getWidth() - (6 * sliderWidth + 3 * padding)) / 2)+60;
    const int startY = (getHeight() - (sliderHeight + 20 + padding)) / 2;

    reverbSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    delaySlider.setBounds(startX + sliderWidth + padding, startY, sliderWidth, sliderHeight);
    highPassSlider.setBounds(startX + 2 * (sliderWidth + padding), startY, sliderWidth, sliderHeight);
    lowPassSlider.setBounds(startX + 3 * (sliderWidth + padding), startY, sliderWidth, sliderHeight);
    gainSlider.setBounds(startX + 4 * (sliderWidth + padding), startY, sliderWidth, sliderHeight);
    freqSlider.setBounds(startX + 5 * (sliderWidth + padding), startY, sliderWidth, sliderHeight);
    textLabel1.setTopLeftPosition(0,0);
    textLabel1.setSize(200, 20);
    textLabel2.setTopLeftPosition(605,180);
    textLabel2.setSize(200, 20);
}
