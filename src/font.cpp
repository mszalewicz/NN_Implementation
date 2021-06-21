#include "font.h"

std::string Font::paint_text(std::string original_string,
                             std::string color_name) {
  original_string.insert(0, color_name);
  original_string.append(this->ENDC);
  return original_string;
}