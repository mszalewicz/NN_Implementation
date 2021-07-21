#include "font.h"

const std::string Font::BLUE = "\033[94m";
const std::string Font::BOLD = "\033[1m";
const std::string Font::CYAN = "\033[96m";
const std::string Font::GREEN = "\033[92m";
const std::string Font::PURPLE = "\033[95m";
const std::string Font::RED = "\033[91m";
const std::string Font::UNDERLINE = "\033[4m";
const std::string Font::YELLOW = "\033[93m";

std::string Font::PaintText(std::string original_string,
							const std::string& color_name) 
{
	const std::string ENDC = "\033[0m";

	original_string.insert(0, color_name);
	original_string.append(ENDC);

	return original_string;
}