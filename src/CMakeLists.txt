add_library(font STATIC font.h font.cpp)

add_library(error_logger STATIC error_logger.h error_logger.cpp)
target_link_libraries(error_logger font)

add_library(matrix STATIC matrix.h matrix.cpp)

add_library(neural_network STATIC neural_network.h neural_network.cpp)
target_link_libraries(matrix)

add_executable(nni main.cpp)
target_link_libraries(nni font)
target_link_libraries(nni matrix)
target_link_libraries(nni error_logger)
target_link_libraries(nni neural_network)
# target_link_libraries(nni imgui)