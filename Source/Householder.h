/*
  ==============================================================================

    Householder.h
    Created: 29 Jul 2023 2:39:32pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include <vector>

class Householder {
    
public:
    Householder(int size);
    
    void inPlaceTransform(std::vector<double>* buffer);
    
    std::vector<std::vector<double>> createHouseholder(int size);
    
private:
    int householder_size; // should always equal num channels
    
    std::vector<std::vector<double>> my_matrix;
};
