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

bool ReadFile(std::vector<std::byte> &buffer, std::string &file_path, 
              ErrorLogger &logger)
{
    std::uintmax_t file_size;
    std::fstream file_stream;
    
    try 
    {
        file_size = std::filesystem::file_size(file_path);
    }
    catch(std::exception &e)
    {
        logger.RecordEvent((std::string)e.what());
        return false;
    }

    try 
    {
        file_stream.open(file_path, std::ios::in | std::ios::binary);
    }
    catch(std::exception &e)
    {
        logger.RecordEvent((std::string)e.what());
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


struct Pixel{
    unsigned int x, y, value;   
};

struct Image
{
    std::vector<Pixel> pixels;
};

struct Label
{
    std::string text;
};

int main(int argc, char *argv[]) 
{
   // if (argc < 2) { usage(); }



    std::vector<std::byte> buffer;

    if( !ReadFile(buffer, file_path, logger) )
    {
        std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
        return 0;
    }

    // unsigned int x = 0;

    // for(auto i : buffer)
    // {
    //     if(x > 12) break;
    //     x += 1;
    //     std::cout << (int)(i) << std::endl;    
    // }

    auto magic_number = int(
                                (unsigned char)(buffer.at(0)) << 24 |
                                (unsigned char)(buffer.at(1)) << 16 |
                                (unsigned char)(buffer.at(2)) << 8  |
                                (unsigned char)(buffer.at(3))
                            );

    auto number_of_entries = int(
                                    (unsigned char)(buffer.at(4)) << 24 |
                                    (unsigned char)(buffer.at(5)) << 16 |
                                    (unsigned char)(buffer.at(6)) << 8  |
                                    (unsigned char)(buffer.at(7))
                                );

    for(unsigned int i = 8; i < buffer.size(); i++)
    {

    }

    std::cout << magic_number << std::endl;
    std::cout << number_of_entries << std::endl;

    // std::cout << std::to_integer<int>(buffer.back()) << std::endl;
    // std::cout << (int)buffer.at(0) << std::endl;
    // std::cout << std::to_integer<int>(buffer.at(buffer.size()-1)) << std::endl;
    

    // int number_of_images;
    // std::vector<Image> images = std::vector<Image>(number_of_images); 

    // Image number_picture;

    return 0;
}