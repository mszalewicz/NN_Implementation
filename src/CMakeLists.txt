add_library(font STATIC font.h font.cpp)

add_library(error_logger STATIC error_logger.h error_logger.cpp)
target_link_libraries(error_logger font)

add_executable(nni main.cpp)
target_link_libraries(nni font)
target_link_libraries(nni error_logger)