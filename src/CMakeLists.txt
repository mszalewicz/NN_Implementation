add_library(
    font
    font.h
    font.cpp
)

add_executable(nni main.cpp)
target_link_libraries(nni font)
target_link_libraries (nni Eigen3::Eigen)