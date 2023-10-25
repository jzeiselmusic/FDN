/*
  ==============================================================================

    Delayer.h
    Created: 29 Jul 2023 2:39:02pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include <random>

using namespace juce;

class Delayer {
    
public:
    Delayer(double length, int num_channels,
            double sampleRate, int rd_seed);
    Delayer(std::vector<int> delay_times, int num_channels);
    
    void process(double sample);
    std::vector<double>* getSamples(void);
    double processAndReturnOneSample(double sample);
    void processParallelSamples(std::vector<double>* buffer);
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delayer);
    
    void addSample(double sample);
    void delaySamples(void);
    
    int buffer_length, random_seed, num_channels;
    
    std::vector<double> input_audio_buffer; // each index in audio buffer is a channel. length = num channels
    
    std::vector<double> output_audio_buffer;
    
    std::vector<std::vector<double>> delay_channels; // dynamic array that holds the delay channels
    
    std::vector<int> delay_amounts; // amount of delay for each channel
    
    std::vector<int> delay_indexes; // current index for each delay channel
    
    std::vector<std::mt19937> seeds_list;
    
};
