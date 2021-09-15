#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>


#include "error_logger.h"
#include "font.h"
#include "matrix.h"
#include "neural_network.h"

//        [] neural network
//        [] adding unit test suite
//        [] teaching
//        [] testing
//        [] summary of the nn results
//        [] documentation
//        [] clean up code

// bool ReadFile(std::vector<std::bool> &buffer, std::string &file_path)
// {
//     std::uintmax_t file_size;
//     std::fstream file_stream;
    
//     try 
//     {
//         file_size = std::filesystem::file_size(file_path);
//     }
//     catch(std::exception &e)
//     {
//         ErrorLogger::RecordEvent((std::string) e.what());
//         return false;
//     }

//     try 
//     {
//         file_stream.open(file_path, std::ios::in | std::ios::binary);
//     }
//     catch(std::exception &e)
//     {
//         ErrorLogger::RecordEvent((std::string) e.what());
//         return false;
//     }

//     buffer = std::vector<std::byte>(file_size);
//     file_stream.read((char*)buffer.data(), buffer.size());

//     file_stream.close();

//     return true;
// }



// std::tuple<Matrix, bool> ReadLabelsIRIS()
// {
//     std::vector<char> buffer;

//     if( !ReadFile(buffer, file_path) )
//     {
//         std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
//         return {{}, false};
//     }


       
// }



// Matrix EncodeLabels(std::vector<unsigned int> labels)
// {
//     std::vector<std::vector<double>> collection_of_encoded_labels;

//     for(auto label : labels)
//     {
//         switch(label)
//         {
//             case 0:
//                 collection_of_encoded_labels.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
//                 break;
//             case 1:
//                 collection_of_encoded_labels.push_back({0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
//                 break;
//             case 2:
//                 collection_of_encoded_labels.push_back({0, 0, 1, 0, 0, 0, 0, 0, 0, 0});
//                 break;
//             case 3:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 1, 0, 0, 0, 0, 0, 0});
//                 break;
//             case 4:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
//                 break;
//             case 5:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 0, 0, 1, 0, 0, 0, 0});
//                 break;
//             case 6:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 0, 0, 0, 1, 0, 0, 0});
//                 break;
//             case 7:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 0, 0, 0, 0, 1, 0, 0});
//                 break;
//             case 8:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 0, 0, 0, 0, 0, 1, 0});
//                 break;
//             case 9:
//                 collection_of_encoded_labels.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 1});
//                 break;
//         }
//     }

//     Matrix encoded_labels = Matrix(collection_of_encoded_labels);

//     return encoded_labels;
// }

// std::tuple<std::vector<unsigned int>, bool> ReadLabels(std::string &file_path)
// {
//     std::vector<std::byte> buffer;

//     if( !ReadFile(buffer, file_path) )
//     {
//         std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
//         return {{}, false};
//     }

//     auto magic_number = unsigned int(
//                                         (unsigned char)(buffer.at(0)) << 24 |
//                                         (unsigned char)(buffer.at(1)) << 16 |
//                                         (unsigned char)(buffer.at(2)) << 8  |
//                                         (unsigned char)(buffer.at(3))
//                                     );

//     // Checks if the the number corresponds to the MNIST specification for IDX file format
//     if(magic_number != 2049) {
//         std::cout << "Invalid file data in '" << file_path << "'.\n\n";
//         return {{}, false};
//     }

//     auto number_of_entries = unsigned int(
//                                              (unsigned char)(buffer.at(4)) << 24 |
//                                              (unsigned char)(buffer.at(5)) << 16 |
//                                              (unsigned char)(buffer.at(6)) << 8  |
//                                              (unsigned char)(buffer.at(7))
//                                          );

//     auto labels = std::vector<unsigned int>(number_of_entries);

//     for(unsigned int i = 8; i < buffer.size(); ++i)
//     {   
//         labels.at(i-8) = (unsigned int) buffer.at(i);
//     }

//     return {labels, true};
// }

// std::tuple<Matrix, bool> ReadImages(std::string &file_path)
// {
//     std::vector<std::byte> buffer;

//     if( !ReadFile(buffer, file_path) )
//     {
//         std::cout << "\nApplication could not open the '" << file_path << "' file.\n\n";
//         return {{}, false};
//     }

//     auto magic_number = unsigned int(
//                                         (unsigned char)(buffer.at(0)) << 24 |
//                                         (unsigned char)(buffer.at(1)) << 16 |
//                                         (unsigned char)(buffer.at(2)) << 8  |
//                                         (unsigned char)(buffer.at(3))
//                                     );

//     if(magic_number != 2051) {
//         std::cout << "Invalid file data in '" << file_path << "'.\n\n";
//         return {{}, false};
//     }

//     auto number_of_images = unsigned int(
//                                              (unsigned char)(buffer.at(4)) << 24 |
//                                              (unsigned char)(buffer.at(5)) << 16 |
//                                              (unsigned char)(buffer.at(6)) << 8  |
//                                              (unsigned char)(buffer.at(7))
//                                          );

//     auto number_of_rows = unsigned int(
//                                           (unsigned char)(buffer.at(8)) << 24 |
//                                           (unsigned char)(buffer.at(9)) << 16 |
//                                           (unsigned char)(buffer.at(10)) << 8  |
//                                           (unsigned char)(buffer.at(11))
//                                       );

//     auto number_of_columns =  unsigned  int(
//                                                (unsigned char)(buffer.at(12)) << 24 |
//                                                (unsigned char)(buffer.at(13)) << 16 |
//                                                (unsigned char)(buffer.at(14)) << 8  |
//                                                (unsigned char)(buffer.at(15))
//                                            );

//     // Constructing images from data:

//     int pixel_amount = number_of_rows * number_of_columns;
    
//     std::vector<std::vector<double>> numbers = std::vector<std::vector<double>>(number_of_images, std::vector<double>(pixel_amount,0));
//     std::vector<double> image_of_number = std::vector<double>(pixel_amount);
    

//     for(auto i = 0; i < number_of_images; ++i)
//     {
//         for (int j = 0; j < pixel_amount; ++j)
//         {
//             image_of_number.at(j) = (double) buffer.at(j+ 16 + (pixel_amount * i));
//         }
//         numbers.at(i) = image_of_number;
//     }

//     Matrix input = Matrix(numbers);

//     return {input, true};
// }

// // TODO: to remove when the visual represenation is in place
// void PrintNumbers(std::vector<std::vector<double>> &test_numbers, int number_of_images_to_print)
// {
//     for (int i = 0; i < number_of_images_to_print; ++i)
//     {
//         auto pixels = test_numbers.at(i);

//         for (int y = 0; y < 28; ++y)
//         {
//             for(int x = 0; x < 28; ++x)
//             {   
//                 if(pixels.at(x+y*28) > 0 && pixels.at(x+y*28) < 128) {std::cout << "x";}
//                 else if(pixels.at(x+y*28) > 128) {std::cout << "@";}
//                 else {std::cout << ".";}        
//             }
//             std::cout << "\n";
//         }

//         std::cout << "\n\n\n";
//     }
// }

void AcknowledgeStepStart(std::string description)
{
    std::cout << Font::PaintText("- ", Font::BLUE)
              << Font::PaintText(description, Font::BLUE)
              << Font::PaintText(" [ ]", Font::BLUE);
} 

void ConfirmExecution()
{
    std::cout << "\b\b\b" 
              << Font::PaintText("[", Font::BLUE) 
              << Font::PaintText("v", Font::GREEN) 
              << Font::PaintText("]", Font::BLUE)  
              << std::endl;
}

void FailedExecution()
{
    std::cout << "\b\b\b" 
              << Font::PaintText("[", Font::BLUE) 
              << Font::PaintText("x", Font::RED) 
              << Font::PaintText("]", Font::BLUE)  
              << std::endl;
}


std::tuple<
            bool, 
            std::vector<std::string>
          >
read_csv(std::string &file_path)
{
    std::vector<std::string> buffer;
    std::fstream file_stream;
    std::string line;

    try 
    {
        file_stream.open(file_path, std::ios::in);
        if(!file_stream.is_open()) throw std::ios::failure("Error opening file!");
    }
    catch(std::exception &e)
    {
        ErrorLogger::RecordEvent((std::string) e.what());
        return {false, {}};
    }


    while(std::getline(file_stream, line))
    {
        buffer.push_back(line);
    }

    file_stream.close();

    return {true, buffer};
}

std::tuple<
            bool, 
            std::vector<std::vector<std::string>>
          >
get_data(std::vector<std::string> file_data)
{
    std::vector<std::vector<std::string>> extracted_data;

    std::string delimiter = ",";

    try
    {
        for(auto i = 1; i < file_data.size(); ++i)
        {
            auto current_string = file_data[i];
            auto start = 0;
            auto end = current_string.find(delimiter);

            std::vector<std::string> entry;
            std::string new_substring;


            while(end != std::string::npos)
            {
                new_substring = current_string.substr(start, end - start);
                start = end + delimiter.length();
                end = current_string.find(delimiter, start);

                entry.push_back(new_substring);
            }

            new_substring = current_string.substr(start, end);
            entry.push_back(new_substring);

            extracted_data.push_back(entry);
        }
    }
    catch(std::exception &e)
    {
        ErrorLogger::RecordEvent((std::string) e.what());
        return {false, {}};
    }

    return {true, extracted_data};
}

std::tuple<
            bool, 
            Matrix, 
            Matrix
          >
separate_and_clean_data(std::vector<std::vector<std::string>> data)
{
    std::vector<std::vector<double>> features_collection;
    std::vector<std::vector<double>> labels_collection;
    Matrix features, labels;

    try
    {
        for(auto i = 0; i < data.size(); ++i)
        {
            std::vector<double> features_entry;

            for(auto j = 0; j < data[0].size() - 1; ++j)
            {
                features_entry.push_back(std::stod(data[i][j]));
            }

            features_collection.push_back(features_entry);
        }

        for(auto i = 0; i < data.size(); ++i)
        {
            auto x = data[i][data[0].size()-1];

            if(x == "setosa") labels_collection.push_back({1, 0, 0});
            if(x == "versicolor") labels_collection.push_back({0, 1, 0});
            if(x == "virginica") labels_collection.push_back({0, 0, 1});
        }    

        features = Matrix(features_collection);
        labels = Matrix(labels_collection);
    }
    catch(std::exception &e)
    {
        ErrorLogger::RecordEvent((std::string) e.what());
        return {false, Matrix(), Matrix()};
    }

    return {true, features, labels};
}

std::tuple<
            std::vector<std::vector<std::string>>,
            std::vector<std::vector<std::string>>
          > 
split_data(std::vector<std::vector<std::string>> complete_set, double size_of_test_set)
{
    int number_of_test_elements = std::floor(complete_set.size() * size_of_test_set);
    int number_of_train_elements = complete_set.size() - number_of_test_elements;

    std::vector<std::vector<std::string>> testing_set = std::vector<std::vector<std::string>>(number_of_test_elements, std::vector<std::string>(4, "          "));
    std::vector<std::vector<std::string>> training_set = std::vector<std::vector<std::string>>(number_of_train_elements, std::vector<std::string>(4, "          "));

    // Randomize positions of the vector elements
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(complete_set.begin(), complete_set.end(), g);

    // Split testing elements
    auto start_iterator = complete_set.begin();
    auto end_iterator = std::next(complete_set.begin(), number_of_test_elements);

    std::copy(start_iterator, end_iterator, testing_set.begin());

    // // Split testing elements
    start_iterator = std::next(complete_set.begin(), number_of_test_elements);
    end_iterator = complete_set.end();

    std::copy(start_iterator, end_iterator, training_set.begin());

    return {training_set, testing_set};
}

int main(int argc, char *argv[]) 
{

    std::cout << std::endl;

    // Initilize error logger - it logs to the current working directory, in file log.txt
    std::string logger_directory = std::filesystem::current_path().string();
    ErrorLogger::Init(logger_directory);

    // TODO read as argument
    std::string file_path = "C:/Users/Urizen/Documents/Projekty/cpp/NN_Implementation/src/iris.csv";

    // -----------------------------------------------------------------------------------------------

    AcknowledgeStepStart("Reading data");

    auto [file_read_correctly, file_content] = read_csv(file_path);
    if(file_read_correctly) ConfirmExecution();
    
    if(!file_read_correctly) 
    {
        std::cout << std::endl
                  << Font::PaintText("Check if file path is correct and file exists.\n", Font::RED)
                  << std::endl;
        return 1;
    }

    // -----------------------------------------------------------------------------------------------

    AcknowledgeStepStart("Data extraction");

    constexpr double testing_set_size = 0.2;

    auto [data_extracted, data] = get_data(file_content);
    auto [training_set, testing_set] = split_data(data, testing_set_size);

    if(data_extracted) ConfirmExecution(); else return 1;

    // -----------------------------------------------------------------------------------------------

    AcknowledgeStepStart("Data cleaning");

    auto [training_cleaning_done, X_train, Y_train] = separate_and_clean_data(training_set);
    auto [testing_cleaning_done, X_test, Y_test] = separate_and_clean_data(testing_set);

    if(training_cleaning_done && testing_cleaning_done) ConfirmExecution(); else return 1;

    // -----------------------------------------------------------------------------------------------

    AcknowledgeStepStart("Bootstrapping neural network");
    ConfirmExecution();

    int height_of_hidden_layer = 4; 

    NeuralNetwork nn = NeuralNetwork(X_train, Y_train, height_of_hidden_layer);
    nn.find_scales();
    nn.scale_to_standard();

    AcknowledgeStepStart("Neural network training");
    nn.train(1);
    ConfirmExecution();

    // AcknowledgeStepStart("Normalize features");
    // auto [normalization_done] = normal_scaler(features);
    // if(normalization_done) ConfirmExecution(); else return 1;


// -------------------------------------------------------------------------------------------------------------------------

    // std::string logger_directory = "C:/Users/Urizen/Documents/Projekty/cpp/NN_Implementation";
    // ErrorLogger::Init(logger_directory);

    // std::cout << Font::PaintText(" - Reading files [ ]", Font::BLUE);

    // std::string labels_path = "C:/Users/Urizen/Music/ungzipped/train-labels-idx1-ubyte";
    // // std::string numbers_path = "C:/Users/Urizen/Music/ungzipped/t10k-images-idx3-ubyte";
    // std::string numbers_path = "C:/Users/Urizen/Music/ungzipped/train-images-idx3-ubyte";



    // auto [test_labels, test_labels_read_correctly] = ReadLabels(labels_path);
    // auto [test_numbers, test_numbers_read_correctly] = ReadImages(numbers_path);
    // auto encoded_test_labels = EncodeLabels(test_labels);

    // if(test_labels_read_correctly && test_numbers_read_correctly) { ConfirmExecution(); }
    // else { FailedExecution(); }

    // std::cout << Font::PaintText(" - Boostrapping neural network [ ]", Font::BLUE);


    // constexpr int height_of_hidden_layer = 120; 
    // auto NN = NeuralNetwork(test_numbers, encoded_test_labels, height_of_hidden_layer);

    // ConfirmExecution();

    // std::cout << Font::PaintText(" - Training neural network [ ]", Font::BLUE);

    // NN.feed_forward();
    // NN.back_propagation();

    // // NN.train(1);

    // ConfirmExecution();
    
    // std::cout << Font::PaintText(" - Predict the results [ ]", Font::BLUE);

    // Matrix results = NN.predict(test_numbers);

    // ConfirmExecution();

    // for(auto i = 0; i < 3; ++i)
    // {
    //     for(auto number : results.values[i])
    //     {
    //         std::cout << number << " ";
    //     }

    //     std::cout << std::endl;
    // }


    // // Matrix weights_1 = Matrix();
    // // Matrix weights_2 = Matrix();

    // // auto tmp = 0;

    // // for(auto label : encoded_test_labels.values)
    // // {
    // //     if(tmp > 2) break;
    // //     for(auto value : label)
    // //     {
    // //         std::cout << value << " ";
    // //     }
    // //     std::cout << std::endl;
    // //     ++tmp;
    // // }

    // // std::cout << std::endl;

    // // if(test_numbers_read_correctly)
    // // {
    // //     PrintNumbers(test_numbers.values, 3);    
    // // }

// -------------------------------------------------------------------------------------------------------------------------

    std::cout << std::endl;

    return 0;
}

    // if(test_numbers_read_correctly)
    // {
    //     PrintNumbers(test_numbers, 5);    
    // }

// Test
    // std::vector<unsigned int> v1{1, 1, 1};
    // std::vector<unsigned int> v2{2, 2, 2};
    // std::vector<unsigned int> v3{3, 2, 2};
    // std::vector<unsigned int> v4{4, 2, 2};

    // std::vector<std::vector<unsigned int>> c1;

    // c1.push_back(v1);
    // c1.push_back(v1);

    // for(auto i = 0; i < c1.size(); ++i)
    //     for(auto j = 0; j < c1[0].size(); ++j)
    //     {
    //         std::cout << c1[i][j];
    //         if(j == c1[0].size() - 1)
    //             std::cout << std::endl;
    //     }

    // std::cout << std::endl;

    // std::vector<std::vector<unsigned int>> c2;

    // c2.push_back(v2);
    // c2.push_back(v3);
    // c2.push_back(v4);

    // for(auto i = 0; i < c2.size(); ++i)
    //     for(auto j = 0; j < c2[0].size(); ++j)
    //     {
    //         std::cout << c2[i][j];
    //         if(j == c2[0].size() - 1)
    //             std::cout << std::endl;
    //     }

    // std::cout << std::endl;


    // Matrix m1 = Matrix(c1);

    // for(auto i = 0; i < m1.values.size(); ++i)
    //     for(auto j = 0; j < m1.values[0].size(); ++j)
    //     {
    //         std::cout << m1.values[i][j];
    //         if(j == m1.values[0].size() - 1)
    //             std::cout << std::endl;
    //     }
    // std::cout << std::endl;

    // Matrix m2 = Matrix(c2);

    // for(auto i = 0; i < m2.values.size(); ++i)
    //     for(auto j = 0; j < m2.values[0].size(); ++j)
    //     {
    //         std::cout << m2.values[i][j];
    //         if(j == m2.values[0].size() - 1)
    //             std::cout << std::endl;
    //     }
    // std::cout << std::endl;

    // Matrix m3 = m1 * m2;
    
    // for(auto i = 0; i < m1.values.size(); ++i)
    //     for(auto j = 0; j < m2.values[0].size(); ++j)
    //     {
    //         std::cout << m3.values[i][j];
    //         if(j == m2.values[0].size() - 1)
    //             std::cout << std::endl;
    //     }