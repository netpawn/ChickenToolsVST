#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleEQAudioProcessor::SimpleEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

SimpleEQAudioProcessor::~SimpleEQAudioProcessor()
{
}


//==============================================================================
const juce::String SimpleEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleEQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleEQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleEQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

float SimpleEQAudioProcessor::getRoomSize() const
{
    return reverb.getParameters().roomSize;
}
float SimpleEQAudioProcessor::getDamping() const
{
    return reverb.getParameters().damping;
}
float SimpleEQAudioProcessor::getDryLevel() const
{
    return reverb.getParameters().dryLevel;
}
float SimpleEQAudioProcessor::getWetLevel() const
{
    return reverb.getParameters().wetLevel;
}
float SimpleEQAudioProcessor::getWidth() const
{
    return reverb.getParameters().width;
}
void SimpleEQAudioProcessor::setRoomSize(float value)
{
    parameters.roomSize = value;
}
void SimpleEQAudioProcessor::setDamping(float value)
{
    parameters.damping = value;
}
void SimpleEQAudioProcessor::setDryLevel(float value)
{
    parameters.dryLevel = value;
}
void SimpleEQAudioProcessor::setWetLevel(float value)
{
    parameters.wetLevel = value;
}
void SimpleEQAudioProcessor::setWidth(float value)
{
    parameters.width = value;
}



//==============================================================================
void SimpleEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //initialize reverb
    
    juce::Reverb::Parameters reverbParams;
    reverbParams.roomSize = reverbRoomSize;
    reverbParams.damping = reverbDamping;
    reverbParams.wetLevel = reverbWetLevel;
    reverbParams.dryLevel = reverbDryLevel;
    reverbParams.width = reverbWidth;
    reverb.setParameters(reverbParams);
    reverb.setSampleRate(sampleRate);
}
void SimpleEQAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    // Check if the parameter ID matches the "Reverb" parameter
    if (parameterID == "Reverb")
    {
        // Update the effect parameter with the new value
        // (replace "reverbParameter" with your actual parameter variable)
        reverbRoomSize = newValue;
    }
}

void SimpleEQAudioProcessor::releaseResources()
{
 
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SimpleEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);

            // Apply reverb to the channel
            reverb.processMono(channelData, buffer.getNumSamples());
        }
}

//==============================================================================
bool SimpleEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleEQAudioProcessor::createEditor()
{
    return new SimpleEQAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleEQAudioProcessor();
}
