/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BiquadFiltersAudioProcessorEditor::BiquadFiltersAudioProcessorEditor (BiquadFiltersAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 250);

    //Parameter Tree States (For Automation)====================================
    outputVolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameters, OUTPUTVOLUME_ID, outputVolumeSlider);

    filterCutoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameters, FILTERCUTOFF_ID, filterCutoffSlider);
    filterResonanceAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameters, FILTERRESONANCE_ID, filterResonanceSlider);

    filterTypeComboBoxAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
        (processor.parameters, FILTERTYPECOMBOBOX_ID, filterTypeComboBox);

    filterBypassAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
        (processor.parameters, FILTERBYPASS_ID, filterBypassButton);

    //SLIDERS ==================================================================
    //Slider Appearances and Properties
    outputVolumeSlider.setSliderStyle(Slider::LinearBarVertical);
    outputVolumeSlider.setRange(-60.0f, 0.0f);
    outputVolumeSlider.setSkewFactor(0.8);
    outputVolumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    outputVolumeSlider.setPopupDisplayEnabled(true, false, this);
    outputVolumeSlider.setTextValueSuffix(" Volume");
    outputVolumeSlider.addListener(this);

    filterCutoffSlider.setSliderStyle(Slider::LinearBarVertical);
    filterCutoffSlider.setRange(40.0f, 19999.99f, 10.0f);
    filterCutoffSlider.setSkewFactor(0.3);
    filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterCutoffSlider.setPopupDisplayEnabled(true, false, this);
    filterCutoffSlider.setTextValueSuffix(" Cutoff");
    filterCutoffSlider.addListener(this);

    filterResonanceSlider.setSliderStyle(Slider::LinearBarVertical);
    filterResonanceSlider.setRange(0.5f, 20.0f);
    filterResonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterResonanceSlider.setPopupDisplayEnabled(true, false, this);
    filterResonanceSlider.setTextValueSuffix(" Resonance");
    filterResonanceSlider.addListener(this);

    //Make Sliders Visible
    addAndMakeVisible(&outputVolumeSlider);
    addAndMakeVisible(&filterCutoffSlider);
    addAndMakeVisible(&filterResonanceSlider);

    //COMBO BOXES ==============================================================
    //ComboBox Appearances and Properties
    filterTypeComboBox.addItem("HP_12db", 1);

    //Make ComboBoxes Visible
    addAndMakeVisible(&filterTypeComboBox);

    //BUTTONS ==================================================================
    //Button Appearances and Properties
    filterBypassButton.setClickingTogglesState(true);

    //Make Buttons Visible
    addAndMakeVisible(&filterBypassButton);
}

BiquadFiltersAudioProcessorEditor::~BiquadFiltersAudioProcessorEditor()
{
}

//==============================================================================
void BiquadFiltersAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void BiquadFiltersAudioProcessorEditor::resized()
{
    filterCutoffSlider.setBounds(10, 35, 20, getHeight() - 60);
    filterResonanceSlider.setBounds(40, 35, 20, getHeight() - 60);

    outputVolumeSlider.setBounds(370, 30, 20, getHeight() - 60);

    filterTypeComboBox.setBounds(40, 5, 140, 20);

    filterBypassButton.setBounds(10, 5, 20, 20);
}

void BiquadFiltersAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    //if (slider == &outputVolumeSlider)
    //{
    //	//processor.outputVolume = pow(10, outputVolumeSlider.getValue() / 20); //10^(slider/20)
    //	processor.outputVolume = outputVolumeSlider.getValue();
    //}
    //if (slider == &filterCutoffSlider)
    //{
    //	processor.filterCutoff = filterCutoffSlider.getValue();
    //}
    //if (slider == &filterResonanceSlider)
    //{
    //	processor.filterResonance = filterResonanceSlider.getValue();
    //}
}

void BiquadFiltersAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox)
{

}

void BiquadFiltersAudioProcessorEditor::buttonClicked(Button* button)
{

}
