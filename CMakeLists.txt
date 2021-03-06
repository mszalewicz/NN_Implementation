cmake_minimum_required(VERSION 3.18.4)

project(NN_Implementation VERSION 0.1.0)

# set(CMAKE_CXX_COMPILER_NAMES  g++ clang++)

# add_compile_options(-std=c++17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # set(STRICT_COMPILE_FLAGS /std:c++latest)
    add_compile_options(/std:c++latest) # /Wall /WX)
    # remove_definitions(/RTC1)
    # set(/std:c++latest /Ox)
else()
    add_compile_options(-std=c++20) # -Wall -Wextra -pedantic #-Werror
endif()


# if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     set(STRICT_COMPILE_FLAGS -Werror=all
#                             -Werror=float-conversion
#                             -Werror=format=2
#                             -Werror=ignored-attributes
#                             -Werror=implicit-fallthrough
#                             -Werror=inconsistent-missing-override
#                             -Werror=old-style-cast
#                             -Werror=unused-parameter
#                             -Werror=unused-variable
#                             -Werror=writable-strings
#                             -Werror=sign-compare
#                             -Wall
#                             -Wextra
#                             -pedantic)
# else()
#     add_compile_options(-Wall -Wextra -pedantic -Werror)
# endif()

# Enables clang-tidy during compilation
# set(CMAKE_CXX_CLANG_TIDY 
#     clang-tidy;
#     -header-filter=.;
#     -checks=*,-google-readability-todo,-llvmlibc-*,-fuchsia-*,-cert-*;)


# Set the executable output folder to /build/bin
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add_subdirectory(external/imgui)
add_subdirectory(src)