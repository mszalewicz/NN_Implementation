#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream> 
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "error_logger.h"
#include "font.h"

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

struct Pixel
{ 
    unsigned int x, y, value;
};

struct Image
{
    std::vector<Pixel> pixels;
};

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
        ErrorLogger::RecordEvent((std::string) e.what());
        return false;
    }

    try 
    {
        file_stream.open(file_path, std::ios::in | std::ios::binary);
    }
    catch(std::exception &e)
    {
        ErrorLogger::RecordEvent((std::string) e.what());
        return false;
    }

    buffer = std::vector<std::byte>(file_size);
    file_stream.read((char*)buffer.data(), buffer.size());

    file_stream.close();

    return true;
}

std::tuple<std::vector<unsigned int>, bool> ReadLabels(std::string &file_path)
{
    std::vector<std::byte> buffer;

    if( !ReadFile(buffer, file_path) )
    {
        std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
        return {{}, false};
    }

    auto magic_number = int(
                                (unsigned char)(buffer.at(0)) << 24 |
                                (unsigned char)(buffer.at(1)) << 16 |
                                (unsigned char)(buffer.at(2)) << 8  |
                                (unsigned char)(buffer.at(3))
                            );

    if(magic_number != 2049) {
        std::cout << "Invalid file data in '" << file_path << "'.\n\n";
        return {{}, false};
    }

    auto number_of_entries = int(
                                    (unsigned char)(buffer.at(4)) << 24 |
                                    (unsigned char)(buffer.at(5)) << 16 |
                                    (unsigned char)(buffer.at(6)) << 8  |
                                    (unsigned char)(buffer.at(7))
                                );

    auto labels = std::vector<unsigned int>(number_of_entries);

    for(unsigned int i = 8; i < buffer.size(); ++i)
    {   
        labels.at(i-8) = (unsigned int) buffer.at(i);
    }

    return {labels, true};
}

std::tuple<std::vector<Image>, bool> ReadImages(std::string &file_path)
{
    std::vector<std::byte> buffer;

    if( !ReadFile(buffer, file_path) )
    {
        std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
        return {{}, false};
    }

    auto magic_number = int(
                          (unsigned char)(buffer.at(0)) << 24 |
                          (unsigned char)(buffer.at(1)) << 16 |
                          (unsigned char)(buffer.at(2)) << 8  |
                          (unsigned char)(buffer.at(3))
                      );

    if(magic_number != 2051) {
        std::cout << "Invalid file data in '" << file_path << "'.\n\n";
        return {{}, false};
    }

    auto number_of_entries = int(
                                (unsigned char)(buffer.at(4)) << 24 |
                                (unsigned char)(buffer.at(5)) << 16 |
                                (unsigned char)(buffer.at(6)) << 8  |
                                (unsigned char)(buffer.at(7))
                            );

    auto number_of_rows = int(
                                 (unsigned char)(buffer.at(8)) << 24 |
                                 (unsigned char)(buffer.at(9)) << 16 |
                                 (unsigned char)(buffer.at(10)) << 8  |
                                 (unsigned char)(buffer.at(11))
                             );

    auto number_of_columns = int(
                                    (unsigned char)(buffer.at(12)) << 24 |
                                    (unsigned char)(buffer.at(13)) << 16 |
                                    (unsigned char)(buffer.at(14)) << 8  |
                                    (unsigned char)(buffer.at(15))
                                );

    // Reconstruct images

    std::vector<Image> numbers;
    Image number_image;
    unsigned int x = 0, y = 0;
 
    for(unsigned int i = 16; i < buffer.size(); ++i)
    {   
        number_image.pixels.push_back( {x, y, (unsigned int) buffer.at(i)} );
        
        ++x;

        if(x == number_of_columns) 
        {
            x = 0;
            ++y; 
        } 
        
        if (y == number_of_rows)
        {
            numbers.push_back(number_image);    
            
            number_image.pixels.clear();

            x = 0;
            y = 0;
        }
    }

    return {numbers, true};
}


int main(int argc, char *argv[]) 
{
   // if (argc < 2) { usage(); }




    auto [test_labels, test_labels_read_bool] = ReadLabels(labels_path);
    auto [test_numbers, test_numbers_read_bool] = ReadImages(numbers_path);

    // for (int i = 0; i < 40; ++i)
    // {
    //     Image image_tmp = numbers.at(i);

    //     for (int y = 0; y < number_of_rows; ++y)
    //     {
    //         for(int x = 0; x < number_of_columns; ++x)
    //         {   
    //             if(image_tmp.pixels.at(x+y*28).value > 0 && image_tmp.pixels.at(x+y*28).value < 128) {std::cout << "x";}
    //             else if(image_tmp.pixels.at(x+y*28).value > 128) {std::cout << "@";}
    //             else {std::cout << ".";}        
    //         }
    //         std::cout << "\n";
    //     }

    //     std::cout << "\n\n\n";
    // }


    // Image image_tmp = numbers.at(7);

    // for (int y = 0; y < number_of_rows; ++y)
    // {
    //     for(int x = 0; x < number_of_columns; ++x)
    //     {   
    //         // if(image_tmp.pixels.at(x+y*28).value > 0) {std::cout << "X";}
    //         // else {std::cout << ".";}       
    //         std::cout << "x': " << image_tmp.pixels.at(x+y*28).x << " y': " << image_tmp.pixels.at(x+y*28).y << "\n";
    //         std::cout << "x: " << x << " y: " << y << "\n";
    //         std::cout << "\n";
    //     }
    //     std::cout << "\n";
    // }
    
    return 0;
}