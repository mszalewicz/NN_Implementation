#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "error_logger.h"
#include "font.h"
#include "matrix.h"
#include "neural_network.h"

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

    // Split training elements
    start_iterator = std::next(complete_set.begin(), number_of_test_elements);
    end_iterator = complete_set.end();

    std::copy(start_iterator, end_iterator, training_set.begin());

    return {training_set, testing_set};
}

int main(int argc, char *argv[]) 
{
    std::cout << Font::PaintText("\nStarting program:\n\n", Font::PURPLE);

    // Initilize error logger - it logs to the current working directory, in file log.txt
    std::string current_working_directory = std::filesystem::current_path().string();
    ErrorLogger::Init(current_working_directory);

    std::string file_path = current_working_directory + "\\iris.csv";

    // -----------------------------------------------------------------------------------------------

    AcknowledgeStepStart("Reading data");

    auto [file_read_correctly, file_content] = read_csv(file_path);
    if(file_read_correctly) ConfirmExecution();
    
    if(!file_read_correctly) 
    {
        std::cout << std::endl
                  << Font::PaintText("Check if 'iris.csv' is in the current working directory\n", Font::RED)
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
    
    int height_of_hidden_layer = 4;
    NeuralNetwork nn = NeuralNetwork(X_train, Y_train, height_of_hidden_layer);

    try
    {
        nn.find_scales();
        nn.scale_to_standard();       
    }
    catch(std::exception &e)
    {
        ErrorLogger::RecordEvent((std::string) e.what());
        return 1;
    }

    ConfirmExecution();

    // -----------------------------------------------------------------------------------------------    

    std::cout << Font::PaintText("\nNeural Network:\n\n", Font::PURPLE);

    nn.work(X_test, Y_test, 1000);   

    std::cout << std::endl;

    return 0;
}