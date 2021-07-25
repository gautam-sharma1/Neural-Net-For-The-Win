cmake_minimum_required(VERSION 3.19)
project(NNFTW)

set(CMAKE_CXX_STANDARD 17)

include_directories(/Users/gautamsharma/Desktop/C++/googletest/googletest/include/)
include_directories(/Users/gautamsharma/Desktop/C++/googletest/googlemock/include/)


link_directories(/Users/gautamsharma/Desktop/C++/googletest/build/lib/)

add_executable(NNFTW main.cpp src/Tensor.cpp)

add_executable(test test/t_Tensor.cpp src/Tensor.cpp)

target_link_libraries(test gtest gmock gtest_main)
