/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BiquadFilters.h"
#include "math.h"

//==============================================================================
BiquadFiltersAudioProcessor::BiquadFiltersAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
parameters(*this, nullptr, "BiquadFiltersState", createParameterLayout())
#endif
{
}

BiquadFiltersAudioProcessor::~BiquadFiltersAudioProcessor()
{
}

//==============================================================================
AudioProcessorValueTreeState::ParameterLayout BiquadFiltersAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    //Sliders
    auto outputVolumeParam = std::make_unique<AudioParameterFloat>(OUTPUTVOLUME_ID, "Output Volume", 
        -128.0f, 0.0f, -3.0f);
    params.push_back(std::move(outputVolumeParam));
    auto filterCutoffParam = std::make_unique<AudioParameterFloat>(FILTERCUTOFF_ID, "Filter Cutoff", 
        40.0f, 19999.99f, 12000.0f);
    params.push_back(std::move(filterCutoffParam));
    auto filterResonanceParam = std::make_unique<AudioParameterFloat>(FILTERRESONANCE_ID, "Filter Resonance", 
        0.5f, 20.0f, 0.6f);
    params.push_back(std::move(filterResonanceParam));

    //ComboBoxes
    auto filterTypeComboBoxParam = std::make_unique<AudioParameterChoice>(FILTERTYPECOMBOBOX_ID, "Filter Type",
        StringArray{ "HP_12db" }, 0);
    params.push_back(std::move(filterTypeComboBoxParam));

    //Buttons
    auto filterBypassParam = std::make_unique<AudioParameterBool>(FILTERBYPASS_ID, "Filter Bypass", true);
    params.push_back(std::move(filterBypassParam));

    return { params.begin(), params.end() };
}
const String BiquadFiltersAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BiquadFiltersAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BiquadFiltersAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BiquadFiltersAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BiquadFiltersAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BiquadFiltersAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BiquadFiltersAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BiquadFiltersAudioProcessor::setCurrentProgram (int index)
{
}

const String BiquadFiltersAudioProcessor::getProgramName (int index)
{
    return {};
}

void BiquadFiltersAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BiquadFiltersAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BiquadFiltersAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BiquadFiltersAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void BiquadFiltersAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //Filter
    if (*parameters.getRawParameterValue(FILTERBYPASS_ID) == true)
    {
        if (*parameters.getRawParameterValue(FILTERTYPECOMBOBOX_ID) == 0)
        {
            calculateCoefficients(*parameters.getRawParameterValue(FILTERCUTOFF_ID), 
                *parameters.getRawParameterValue(FILTERRESONANCE_ID), 0, getSampleRate());

            biquadFilter(buffer, totalNumInputChannels);
        }
    }

    //calculateCoefficients(*parameters.getRawParameterValue(FILTERCUTOFF_ID),
    //    *parameters.getRawParameterValue(FILTERRESONANCE_ID), 0, (float)getSampleRate());

    //biquadFilter(buffer, totalNumInputChannels);

    //Output Volume
    outputVolumeHandling(buffer, totalNumInputChannels);
}

void BiquadFiltersAudioProcessor::outputVolumeHandling(AudioBuffer<float>& buffer, int inputChannels)
{
    //*************** TRY MAKING CUSTOM GAIN RAMP ******************************
    for (int channel = 0; channel < inputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        auto outputVolumeSliderValue = parameters.getRawParameterValue(OUTPUTVOLUME_ID);

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            channelData[i] = buffer.getSample(channel, i);

            channelData[i] *= pow(10, (*outputVolumeSliderValue / 20));
        }
    }
}

//==============================================================================
bool BiquadFiltersAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BiquadFiltersAudioProcessor::createEditor()
{
    return new BiquadFiltersAudioProcessorEditor (*this);
}

//==============================================================================
void BiquadFiltersAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<XmlElement> xmlFile(parameters.state.createXml());
    copyXmlToBinary(*xmlFile, destData);
}

void BiquadFiltersAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BiquadFiltersAudioProcessor();
}
