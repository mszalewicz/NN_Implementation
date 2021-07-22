#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream> 
#include <iostream>
#include <string>
#include <vector>

#include "error_logger.h"
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
    constexpr auto kSlopeCoefficient = 0.01f; 
    if (x < 0) { x *= kSlopeCoefficient; }
}

// void Usage() 
// {
//     // std::string description = 
//     // "
//     // test
//     // ";

//     std::cout << "\n" 
//               << Font::PaintText("Usage: ", Font::YELLOW) << "nni arg1 arg2"
//               << "\n\n"
//               << "\t" << "something something";  // TODO
// }

bool ReadFile(std::vector<std::byte> &buffer, std::string &file_path)
{
    std::uintmax_t file_size;
    std::fstream file_stream;
    
    try 
    {
        file_size = std::filesystem::file_size(file_path);
    }
    catch(std::exception &e)
    {
        std::cerr << Font::PaintText(e.what(), Font::RED) << std::endl;

        return false;
    }

    try 
    {
        file_stream.open(file_path, std::ios::in | std::ios::binary);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return false;
    }

    buffer = std::vector<std::byte>(file_size);
    file_stream.read((char*)buffer.data(), buffer.size());

    file_stream.close();

    return true;
}

// void ReadSettigns()
// {
//     std::fstream settings_file();
// }


struct Image
{
    std::vector<std::pair<uint>> pixels;
};



int main(int argc, char *argv[]) 
{
   // if (argc < 2) { usage(); }

    std::string errMsg = "An error :(";

    ErrorLogger logger = ErrorLogger(logger_directory);
    logger.RecordEvent(errMsg);

    std::vector<std::byte> buffer;

    if( !ReadFile(buffer, file_path) )
    {
        std::cout << "Application could not open the file " << file_path;
        return 0;
    }

    int number_of_images;
    std::vector<Image> images = std::vector<Image>(number_of_images); 

    Image number_image;

    return 0;
}