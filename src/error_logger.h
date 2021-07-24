#pragma once

#include <string>

class ErrorLogger 
{
    ///
    public:
        ErrorLogger(std::string&);
        void static Init(std::string&);
        void static RecordEvent(std::string);

    private:
        std::string static output_file_path;
};