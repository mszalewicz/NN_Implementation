#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>

#include "error_logger.h"
#include "font.h"

ErrorLogger::ErrorLogger(std::string &path)
{
    std::string current_date = std::chrono::format("%y_%m_%d", std::chrono::system_clock::now());
    std::cout << "\n" << current_date << "\n";
    this->output_file_path = path + "/log.txt"; 
}

void ErrorLogger::RecordEvent(std::string &message)
{
    std::fstream file_stream;

    try
    {
        file_stream.open(this->output_file_path,
                         std::ios::out | std::ios::app);
    }
    catch(std::exception &e)
    {
        std::cerr << "ErrorLogger::Run(): "
                  << e.what() 
                  << std::endl;
    }

    std::cerr << Font::PaintText(message, Font::RED) << std::endl;
    file_stream << "[" 
                << std::chrono::system_clock::now() 
                << "]\n\n"
                << message
                << "\n\n---------------------------------------\n\n";
    file_stream.close();
}