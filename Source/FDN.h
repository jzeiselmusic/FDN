/*
  ==============================================================================

    FDN.h
    Created: 16 Oct 2023 11:58:04am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Delayer.h"
#include "Hadamard.h"
#include "Householder.h"

/* FDN module should have N inputs and N outputs */

/* needs to perform delay and feedback into the input
   plus a householder (or other) matrix step on the feedback path */
class FDN
{
public:
    FDN(int size, std::vector<int> delay_times, double decay);
    ~FDN(void);
    std::vector<double> processFdnArray(std::vector<double> buffer);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FDN);
    
    int size;
    double decay;
    
    /* N channel delay module */
    Delayer* delay_module;
    
    /* N channel householder matrix */
    Householder* householder_matrix;
    
    std::vector<double> output_buffer;
    
    std::vector<double> feedback_buffer;
    

};
