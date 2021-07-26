#include <iostream>
#include "include/Tensor.h"

int main() {
    Tensor<float> t ({1,2.555,3,4,5,6.667,7,8});
    Tensor<float> t1({1,2,3,4,5});
    Tensor<float> t2({1,2,3,4,5});
    Tensor<float> t3 = t1+t2;
    std::cout<<t1;
    std::cout<<t2;
    std::cout<<t3;
    //std::cout << t;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
