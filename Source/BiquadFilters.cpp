/*
  ==============================================================================

    BiquadFilters.cpp
    Created: 8 Apr 2020 9:26:51am
    Author:  rossk

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "BiquadFilters.h"

BiquadFilters::BiquadFilters()
{

}

BiquadFilters::~BiquadFilters()
{

}

void BiquadFilters::biquadFilter(AudioBuffer<float>& buffer, int inputChannels)
{
    const float* inputChannelData;
    float* outputChannelData = {};

	//Process Incoming Samples 
	for (int i = 0; i < buffer.getNumSamples(); ++i)
	{
		for (int channel = 0; channel < inputChannels; ++channel)
		{
			inputChannelData = buffer.getReadPointer(channel);
			outputChannelData = buffer.getWritePointer(channel);

			input2 = input1; //x(n - 2)
			input1 = input; //x(n - 1)
			input = inputChannelData[i]; //x(n)

			output2 = output1; //y(n - 2)
			output1 = output; //y(n - 1)

			//y(n) = b0*x(n) + b1*x(n-1) + b2*x(n-2) - a0*y(n-1) - a1*y(n-2)
			output = (a0 * input) + (a1 * input1) + (a2 * input2) - (b0 * output1) - (b1 * output2);

			outputChannelData[i] = output; //y(n)
		}
	}
}

float BiquadFilters::calculateCoefficients(float cutoff, float q, int type, double sampleRate)
{
	//Is this function necessary? Could the Coefficients be calc'd using the constructor? 
	//Or called in constructor / biquadFilter()?

	if (type == 0) //Second Order High Pass
	{
		//q = 0.5f + (19.5f * q);
		float theta = (pi * cutoff) / (float)sampleRate;
		float d = 1.0f / q;
		float beta = 0.5f * ((1.0f - (d / 2.0f) * sin(theta)) / (1.0f + (d / 2.0f) * sin(theta)));
		float gamma = (0.5f + beta) * cos(theta);
		a0 = (0.5f + beta + gamma) / 2.0f;
		a1 = -(0.5f + beta + gamma);
		a2 = a0;
		b0 = -2.0f * gamma;
		b1 = 2.0f * beta;
	}

	return a0, a1, a2, b0, b1;
}