add_library(font STATIC font.h font.cpp)

add_library(errorlogger STATIC errorlogger.h errorlogger.cpp)
target_link_libraries(errorlogger font)

add_executable(nni main.cpp)
target_link_libraries(nni font)
target_link_libraries(nni errorlogger)
# target_link_libraries (nni Eigen3::Eigen)