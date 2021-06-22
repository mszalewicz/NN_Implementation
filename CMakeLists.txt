cmake_minimum_required(VERSION 3.18.4)

set(CMAKE_CXX_COMPILER_NAMES clang++-12 clang++ g++)

add_compile_options(-std=c++11)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(STRICT_COMPILE_FLAGS -Werror=all
                            -Werror=float-conversion
                            -Werror=format=2
                            -Werror=ignored-attributes
                            -Werror=implicit-fallthrough
                            -Werror=inconsistent-missing-override
                            -Werror=old-style-cast
                            -Werror=unused-parameter
                            -Werror=unused-variable
                            -Werror=writable-strings
                            -Werror=sign-compare
                            -Wall
                            -Wextra
                            -pedantic)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# // Enables clang-tidy during compilation
# set(CMAKE_CXX_CLANG_TIDY 
#     clang-tidy-12;
#     -header-filter=.;
#     -checks=*,-google-readability-todo,-llvmlibc-*,-fuchsia-*,-cert-*;)


# Set the executable output folder to /build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(NNI VERSION 0.0.1)

find_package(Eigen3 3.3 REQUIRED)

add_subdirectory(src)