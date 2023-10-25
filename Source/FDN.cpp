/*
  ==============================================================================

    FDN.cpp
    Created: 16 Oct 2023 11:58:08am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "FDN.h"

FDN::FDN(int size, std::vector<int> delay_times, double decay)
{
    this->delay_module = new Delayer(delay_times, size);
    
    /* set the output buffer to all zeros */
    this->output_buffer.resize(size);
    std::fill(output_buffer.begin(), output_buffer.end(), 0.0);
    
    this->feedback_buffer.resize(size);
    std::fill(feedback_buffer.begin(), feedback_buffer.end(), 0.0);
    
    this->householder_matrix = new Householder(size);
    
    this->size = size;
    
    this->decay = decay;
}

FDN::~FDN(void)
{
    delete delay_module;
    delete householder_matrix;
}

std::vector<double> FDN::processFdnArray(std::vector<double> input_from_diffuser_stage)
{
    /*
     
     
     >>-----------{input_buffer}---|delay_module|----{output_buffer}---->>
                           |                              |
                    {feedback_buffer}                     |
                           |                              |
                            <<----|matrix_module|--------<<
     
     */
    std::vector<double> input_buffer;
    input_buffer.resize(size);
    std::fill(input_buffer.begin(), input_buffer.end(), 0.0);
    
    for (int i = 0; i < size; ++i)
    {
        input_buffer[i] = input_from_diffuser_stage[i] + feedback_buffer[i];
    }
    
    delay_module->processParallelSamples(&input_buffer);
    
    std::vector<double>* output = delay_module->getSamples();
    
    householder_matrix->inPlaceTransform(output);
    
    for (int i = 0; i < size; ++i)
    {
        feedback_buffer[i] = output->at(i) * (decay);
    }
    
    return *output;
}
