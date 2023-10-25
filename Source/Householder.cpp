/*
  ==============================================================================

    Householder.cpp
    Created: 29 Jul 2023 2:39:27pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Householder.h"

Householder::Householder(int size)
{
    householder_size = size;
    my_matrix = createHouseholder(size);
}

void Householder::inPlaceTransform(std::vector<double>* buffer)
{
    // input is an array of pointers to each channel's current value
    
    // we want to do a matrix multiplication with our householder matrix
    // and then put the result back in the current values matrix
    
    std::vector<double> output_vals(this->householder_size);
    std::fill(output_vals.begin(), output_vals.end(), 0.0);
    
    // dot products
    for (int i = 0; i < householder_size; ++i)
    {
        for (int j = 0; j < householder_size; ++j)
        {
            output_vals[i] += my_matrix[i][j] * buffer->at(j);
        }
    }
    
    // put the output vals into the current vals
    for (int i = 0; i < householder_size; ++i)
    {
        buffer->at(i) = output_vals[i];
    }
}

std::vector<std::vector<double>> Householder::createHouseholder(int size)
{
    /* create and return a dynamic vector that is a square householder matrix */
    
    /* create the empty matrix */
    std::vector<std::vector<double>> temp;
    
    for (int i = 0; i < size; ++i)
    {
        std::vector<double> temp_a;
        for (int j = 0; j < size; ++j)
        {
            temp_a.push_back(0.0);
        }
        temp.push_back(temp_a);
    }
    
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i == j)
            {
                temp[i][j] = 1.0 - (2.0 / (double)size);
            }
            else
            {
                temp[i][j] = 0.0 - (2.0 / (double)size);
            }
        }
    }
    
    return temp;
}
