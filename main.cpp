#include <iostream>
#include "src/Tensor.h"

int main() {
    Tensor<float> t ({1,2.555,3,4,5,6.667,7,8});
    std::cout << t;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
