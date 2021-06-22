#ifndef _NN_IMPLEMENTATION_SRC_FONT_H
#define _NN_IMPLEMENTATION_SRC_FONT_H

#include <string>

class Font {
  /// Used for changing the terminal font color or form.

 public:
  static const std::string BLUE;
  static const std::string BOLD;
  static const std::string CYAN;
  static const std::string GREEN;
  static const std::string PURPLE;
  static const std::string RED;
  static const std::string UNDERLINE;
  static const std::string YELLOW;

  std::string static paint_text(std::string original_string,
                                const std::string& color_name);
};

#endif