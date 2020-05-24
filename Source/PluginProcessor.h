/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "BiquadFilters.h"

#define FILTERCUTOFF_ID "filterCutoff"
#define FILTERRESONANCE_ID "filterResonance"
#define FILTERTYPECOMBOBOX_ID "filterTypeBox"
#define FILTERBYPASS_ID "filterBypass"

#define OUTPUTVOLUME_ID "outputVolume"

//==============================================================================
/**
*/
class BiquadFiltersAudioProcessor  : public AudioProcessor, public BiquadFilters
{
public:
    //==============================================================================
    BiquadFiltersAudioProcessor();
    ~BiquadFiltersAudioProcessor();

    //==============================================================================
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void outputVolumeHandling(AudioBuffer<float>& buffer, int inputChannels);

    //==============================================================================
    //Global Objects and Variables
    //==============================================================================

    //Control Parameter Values======================================================
    AudioProcessorValueTreeState parameters;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BiquadFiltersAudioProcessor)
};
