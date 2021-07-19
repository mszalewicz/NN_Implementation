#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "font.h"

//        [] handle the IDX files
//        [] neural network
//        [] adding unit test suite
//        [] teaching
//        [] testing
//        [] summary of the nn results
//        [] error logging
//        [] documentation

void LeakyReLU(float &x) 
{
    /// Implementation of the Leaky ReLU activation function.
    /// https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Leaky_ReLU

    if (x < 0) { x *= 0.01; }
}

void usage() 
{
    // std::string description = 
    // "
    // test
    // ";
    
    std::cout << "\n" 
              << Font::paint_text("Usage: ", Font::YELLOW) << "nni arg1 arg2"
              << "\n\n"
              << "\t" << "something something";  // TODO
}

int main(int argc, char **argv) 
{
    if (argc < 2) { usage(); }

    std::cout << "test" << std::endl;

    return 0;
}