#pragma once

#include <string>

class Font 
{
    /// Adds color to terminal font and manipulates terminal lines
    public:
        static const std::string BLUE;
        static const std::string BOLD;
        static const std::string CYAN;
        static const std::string GREEN;
        static const std::string PURPLE;
        static const std::string RED;
        static const std::string UNDERLINE;
        static const std::string YELLOW;

        std::string static PaintText(std::string original_string, 
                                     const std::string& color_name);
        
        void static erase_n_lines(int n);
};