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

    auto magic_number = unsigned int(
                                        (unsigned char)(buffer.at(0)) << 24 |
                                        (unsigned char)(buffer.at(1)) << 16 |
                                        (unsigned char)(buffer.at(2)) << 8  |
                                        (unsigned char)(buffer.at(3))
                                    );

    if(magic_number != 2049) {
        std::cout << "Invalid file data in '" << file_path << "'.\n\n";
        return {{}, false};
    }

    auto number_of_entries = unsigned int(
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

std::tuple<std::vector<std::vector<unsigned int>>, bool> ReadImages(std::string &file_path)
{
    std::vector<std::byte> buffer;

    if( !ReadFile(buffer, file_path) )
    {
        std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
        return {{}, false};
    }

    auto magic_number = unsigned int(
                                        (unsigned char)(buffer.at(0)) << 24 |
                                        (unsigned char)(buffer.at(1)) << 16 |
                                        (unsigned char)(buffer.at(2)) << 8  |
                                        (unsigned char)(buffer.at(3))
                                    );

    if(magic_number != 2051) {
        std::cout << "Invalid file data in '" << file_path << "'.\n\n";
        return {{}, false};
    }

    auto number_of_images = unsigned int(
                                             (unsigned char)(buffer.at(4)) << 24 |
                                             (unsigned char)(buffer.at(5)) << 16 |
                                             (unsigned char)(buffer.at(6)) << 8  |
                                             (unsigned char)(buffer.at(7))
                                         );

    auto number_of_rows = unsigned int(
                                          (unsigned char)(buffer.at(8)) << 24 |
                                          (unsigned char)(buffer.at(9)) << 16 |
                                          (unsigned char)(buffer.at(10)) << 8  |
                                          (unsigned char)(buffer.at(11))
                                      );

    auto number_of_columns =  unsigned  int(
                                               (unsigned char)(buffer.at(12)) << 24 |
                                               (unsigned char)(buffer.at(13)) << 16 |
                                               (unsigned char)(buffer.at(14)) << 8  |
                                               (unsigned char)(buffer.at(15))
                                           );


    

    // Constructing images from data:

    int pixel_amount = number_of_rows * number_of_columns;
    
    std::vector<std::vector<unsigned int>> numbers = std::vector<std::vector<unsigned int>>(number_of_images);
    std::vector<unsigned int> image_of_number = std::vector<unsigned int>(pixel_amount);
    

    for(auto i = 0; i < number_of_images; ++i)
    {
        for (int j = 0; j < pixel_amount; ++j)
        {
            image_of_number.at(j) = (unsigned int) buffer.at(j+ 16 + (pixel_amount * i));
        }
        numbers.at(i) = image_of_number;
    }

    return {numbers, true};
}

// TODO: to remove when the visual represenation is in place
void PrintNumbers(std::vector<std::vector<unsigned int>> &test_numbers, int number_of_images_to_print)
{
    for (int i = 0; i < number_of_images_to_print; ++i)
    {
        auto pixels = test_numbers.at(i);

        for (int y = 0; y < 28; ++y)
        {
            for(int x = 0; x < 28; ++x)
            {   
                if(pixels.at(x+y*28) > 0 && pixels.at(x+y*28) < 128) {std::cout << "x";}
                else if(pixels.at(x+y*28) > 128) {std::cout << "@";}
                else {std::cout << ".";}        
            }
            std::cout << "\n";
        }

        std::cout << "\n\n\n";
    }
}

int main(int argc, char *argv[]) 
{

    // std::string logger_directory = "C:/Users/Urizen/Documents/Projekty/cpp/NN_Implementation";
    // ErrorLogger::Init(logger_directory);



    // auto [test_labels, test_labels_read_correctly] = ReadLabels(labels_path);
    auto [test_numbers, test_numbers_read_correctly] = ReadImages(numbers_path);

    // if(test_numbers_read_correctly)
    // {
    //     PrintNumbers(test_numbers, 3);    
    // }
    
    return 0;
}