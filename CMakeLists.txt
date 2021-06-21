cmake_minimum_required(VERSION 3.18.4)

project(NNI VERSION 0.0.1)

add_compile_options(-std=c++11)

# Show all warnings and treat as errors
add_compile_options(-Wall -Wextra -pedantic -Werror)

# // Enables clang-tidy during compilation
# TODO: Uncomment below lines when ready to clean code.
# set(CMAKE_CXX_CLANG_TIDY 
#   clang-tidy-12;
#   -header-filter=./src;
#   -checks=*;)

# Set the executable output folder to /build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add_subdirectory(third_party)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen-3.3.9)

# #  Requirements
# find_package(Eigen3 3.3 REQUIRED)
# target_link_libraries (nni Eigen3::Eigen) <- add this line under add_executable()

add_subdirectory(src)