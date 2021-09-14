#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>

#include "error_logger.h"
#include "font.h"

ErrorLogger::ErrorLogger(std::string& path)
{
    output_file_path = path + "/log.txt"; 
}

void ErrorLogger::Init(std::string& path)
{
    output_file_path = path + "/log.txt";
}

void ErrorLogger::RecordEvent(std::string message)
{
    std::fstream file_stream;

    try
    {
        file_stream.open(output_file_path,
                         std::ios::out | std::ios::app);
    }
    catch(std::exception& e)
    {
        std::cerr << "ErrorLogger::Run(): "
                  << e.what() 
                  << std::endl;
    }

    std::cout << "\b\b\b" 
              << Font::PaintText("[", Font::BLUE) 
              << Font::PaintText("x", Font::RED) 
              << Font::PaintText("]", Font::BLUE) 
              << std::endl 
              << std::endl;

    std::cerr << Font::PaintText(message, Font::RED) << std::endl;

    if(output_file_path != (std::string)"")
    {
        file_stream << "[" 
                    << std::chrono::system_clock::now() 
                    << "]\n\n"
                    << message
                    << "\n\n---------------------------------------\n\n";        
    }

    file_stream.close();
}

std::string ErrorLogger::output_file_path = "";