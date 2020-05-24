/*
  ==============================================================================

    BiquadFilters.h
    Created: 8 Apr 2020 9:26:51am
    Author:  rossk

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class BiquadFilters
{
public:
    BiquadFilters();
    ~BiquadFilters();

    void biquadFilter(AudioBuffer<float>& buffer, int inputChannels);
    float calculateCoefficients(float cutoff, float q, int type, double sampleRate);

    float input1 = 0; float input2 = 0; float input = 0;
    float output1 = 0; float output2 = 0; float output = 0;

    float a0 = 0; float a1 = 0; float a2 = 0; float b0 = 0; float b1 = 0;

    //float pi = 3.141592653589793;
    float pi = 3.1415926535f;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BiquadFilters)
};