cmake_minimum_required(VERSION 3.19)
project(NNFTW)

set(CMAKE_CXX_STANDARD 20)

include_directories(/Users/gautamsharma/Desktop/C++/googletest/googletest/include/)
include_directories(/Users/gautamsharma/Desktop/C++/googletest/googlemock/include/)

include_directories(include/)

link_directories(/Users/gautamsharma/Desktop/C++/googletest/build/lib/)

add_executable(NNFTW main.cpp src/Tensor.cpp src/Tensor2D.cpp src/Utility.cpp)

add_executable(test test/t_Tensor.cpp test/t_Tensor2D.cpp src/Tensor.cpp src/Tensor2D.cpp src/Utility.cpp)

target_link_libraries(test gtest gmock gtest_main)
