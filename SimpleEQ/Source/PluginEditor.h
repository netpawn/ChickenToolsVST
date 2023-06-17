#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
   
    
    void resized() override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;
    
    //UI COMPONENTS
    juce::Slider reverbSlider;
    juce::Slider delaySlider;
    juce::Slider highPassSlider;
    juce::Slider lowPassSlider;
    juce::Slider gainSlider;
    juce::Slider freqSlider;
    
    juce::Label textLabel1;
    juce::Label textLabel2;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
