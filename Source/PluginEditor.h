/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BiquadFilters.h"

//==============================================================================
/**
*/
class BiquadFiltersAudioProcessorEditor  : public AudioProcessorEditor,
    public Slider::Listener, public ComboBox::Listener, public Button::Listener
{
public:
    BiquadFiltersAudioProcessorEditor (BiquadFiltersAudioProcessor&);
    ~BiquadFiltersAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(ComboBox* comboBox) override;
    void buttonClicked(Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BiquadFiltersAudioProcessor& processor;

    //Sliders
    Slider outputVolumeSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputVolumeAttachment;

    Slider filterCutoffSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;

    Slider filterResonanceSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    //ComboBoxes
    ComboBox filterTypeComboBox;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeComboBoxAttachment;

    //Buttons
    ToggleButton filterBypassButton;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> filterBypassAttachment;

public:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BiquadFiltersAudioProcessorEditor)
};
