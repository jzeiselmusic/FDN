/*
  ==============================================================================

    utilities.h
    Created: 29 Jul 2023 3:26:27pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once
#include <random>

inline int incrementModulo(const int current_value, const int max_length)
{
    return current_value + 1 >= max_length ? 0 : current_value + 1;
}

inline int getRandomMult(std::mt19937 gen)
{
    // return either 1 or -1
    
    std::uniform_int_distribution<> mult_distrib(0,1);
    
    int randomMult = mult_distrib(gen);
    
    return (randomMult == 0) ? -1 : 1;
}

inline int getRandomInRange(int maxValue, std::mt19937 gen)
{
    // return a random number between 0 to maxValue
    
    // Define new distribution between 0 and maxValue
    std::uniform_int_distribution<> total_distrib(0, maxValue - 1);
    
    // random int between 0 and maxValue
    int randomValue = total_distrib(gen);
    
    // return the random value
    return randomValue;
}
