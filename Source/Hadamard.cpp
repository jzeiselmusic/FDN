/*
  ==============================================================================

    Hadamard.cpp
    Created: 14 Oct 2023 1:29:42pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Hadamard.h"

Hadamard::Hadamard(int size)
{
    hadamard_size = size;
    
    if (size != 4 && size != 8 && size != 16)
    {
        throw std::runtime_error("can only be 4,8,or 16 channels");
    }
}

void Hadamard::inPlaceTransform(std::vector<double> *buffer)
{
    std::vector<double> output_vals(hadamard_size);
    std::fill(output_vals.begin(), output_vals.end(), 0.0);
    
    // dot products
    for (int i = 0; i < hadamard_size; ++i)
    {
        for (int j = 0; j < hadamard_size; ++j)
        {
            switch(hadamard_size)
            {
                case 4:
                    output_vals[i] += hadamard_four[i][j] * buffer->at(j);
                    break;
                case 8:
                    output_vals[i] += hadamard_eight[i][j] * buffer->at(j);
                    break;
                case 16:
                    output_vals[i] += hadamard_sixteen[i][j] * buffer->at(j);
                    break;
                default:
                    throw std::runtime_error("can only be 4,8,or 16 channels");
            }
        }
        // now scale
        output_vals[i] *= (1.0 / sqrt((double)hadamard_size));
    }
    
    // put the output vals into the current vals
    for (int i = 0; i < hadamard_size; ++i)
    {
        buffer->at(i) = output_vals[i];
    }
}
