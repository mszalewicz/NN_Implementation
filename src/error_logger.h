#pragma once

#include <string>

class ErrorLogger 
{
    ///
    public:
        ErrorLogger(std::string&);
        void RecordEvent(std::string&);

    private:
        std::string output_file_path;
};