/*
  ==============================================================================

    Delayer.cpp
    Created: 29 Jul 2023 2:38:53pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Delayer.h"
#include <random>
#include "utilities.h"

using namespace juce;

Delayer::Delayer(double length, int num_channels,
                 double sampleRate, int rd_seed)
{
    /* create the input and output buffers */
    for (int i = 0; i < num_channels; ++i)
    {
        input_audio_buffer.push_back(0.0);
        output_audio_buffer.push_back(0.0);
    }
    
    /* constructor for a multi-channel delay module */
    this->buffer_length = length*sampleRate + 1;
    
    this->num_channels = num_channels;
    
    /* create delay channels */
    for (int i = 0; i < num_channels; ++i)
    {
        std::vector<double> temp(buffer_length);
        std::fill(temp.begin(), temp.end(), 0.0);
        delay_channels.push_back(temp);
    }
    
    /* now we need to create random delay times for each channel */
    random_seed = rd_seed;
    for (int i = 0; i < num_channels; ++i)
    {
        std::mt19937 temp(random_seed + i);
        
        int increment = buffer_length / num_channels;
        
        delay_amounts.push_back(increment*(i+1) - getRandomInRange(increment, temp));
    }
    
    
    /* start the delay indexes at 0 */
    for (int i = 0; i < num_channels; ++i)
    {
        delay_indexes.push_back(0);
    }
}

Delayer::Delayer(std::vector<int> delay_times, int num_channels)
{
    /* create the input and output buffers */
    for (int i = 0; i < num_channels; ++i)
    {
        input_audio_buffer.push_back(0.0);
        output_audio_buffer.push_back(0.0);
    }
    
    /* constructor for a multi-channel delay module */
    auto max = max_element(std::begin(delay_times), std::end(delay_times));
    this->buffer_length = max[0] + 1;
    
    this->num_channels = num_channels;
    
    /* create delay channels */
    for (int i = 0; i < num_channels; ++i)
    {
        std::vector<double> temp(buffer_length);
        std::fill(temp.begin(), temp.end(), 0.0);
        delay_channels.push_back(temp);
    }
    
    /* now we need to create delay times for each channel */
    for (int i = 0; i < num_channels; ++i)
    {
        delay_amounts.push_back(delay_times[i]);
    }
    
    
    /* start the delay indexes at 0 */
    for (int i = 0; i < num_channels; ++i)
    {
        delay_indexes.push_back(0);
    }
}

void Delayer::addSample(double sample)
{
    for (int i = 0; i < num_channels; ++i)
    {
        input_audio_buffer[i] = sample;
    }
}

void Delayer::delaySamples(void)
{
    // first we read the latest sample that was just added from the channel buffer
    
    // then we read the value from the current delay buffer
    // and put that value in the corresponding channel
    
    // then we put the latest channel sample into the delay buffer
    
    // increment the delay buffer pointer
    
    for (int i = 0; i < num_channels; ++i)
    {
        double latest_value = input_audio_buffer[i]; // should be the same every pass through
        
        double current_delay_buffer_value = delay_channels[i][delay_indexes[i]];
        
        output_audio_buffer[i] = current_delay_buffer_value;
        
        delay_channels[i][delay_indexes[i]] = latest_value;
        
        delay_indexes[i] = incrementModulo(delay_indexes[i], delay_amounts[i]);
    }
}

void Delayer::process(double sample)
{
    addSample(sample);
    
    delaySamples();
}

double Delayer::processAndReturnOneSample(double sample)
{
    addSample(sample);
    
    delaySamples();
    
    double total = 0.0;
    
    for (int i = 0; i < num_channels; ++i)
    {
        total += output_audio_buffer[i];
    }
    
    return total / (double)num_channels;
}

void Delayer::processParallelSamples(std::vector<double>* buffer)
{
    for (int i = 0; i < num_channels; ++i)
    {
        input_audio_buffer[i] = buffer->at(i);
    }
    
    delaySamples();
}

std::vector<double>* Delayer::getSamples()
{
    return &output_audio_buffer;
}

