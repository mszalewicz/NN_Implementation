#ifndef FONT_H
#define FONT_H

#include <string>

class Font {
  /// Used for changing the terminal font color or form.

 public:
  std::string PURPLE = "\033[95m";
  std::string BLUE = "\033[94m";
  std::string CYAN = "\033[96m";
  std::string GREEN = "\033[92m";
  std::string YELLOW = "\033[93m";
  std::string RED = "\033[91m";
  std::string ENDC = "\033[0m";
  std::string BOLD = "\033[1m";
  std::string UNDERLINE = "\033[4m";

  std::string paint_text(std::string original_string, std::string color_name);
};

#endif