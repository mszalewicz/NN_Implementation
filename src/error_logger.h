#pragma once

#include <string>

class ErrorLogger 
{
    /// Logs errors to the local 'log.txt' file
    public:
        ErrorLogger(std::string&);
        void static Init(std::string&);
        void static RecordEvent(std::string);

    private:
        std::string static output_file_path;
};