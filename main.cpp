#include <iostream>
#include <vector>
#include "include/Tensor.h"
#include "include/Tensor2D.h"
#include "include/Utility.h"
using namespace std;
using namespace NNFTW;

int main() {
    Tensor<float> t ({1,2.555,3,4,5,6.667,7,8});
    Tensor<float> t1({1,5});
//    t.multiply(t1);
    Tensor2D<float> t3 = {t1,t1,t1};
    auto t4 = t3.transpose();
    auto t5 = t3;
    cout<<t5;
    Tensor2D<float> t6 = t3*t4;
    cout<<t6<<endl;
    Tensor2D<float> t7 = t6+t6;
    cout<<t7<<endl;
    Tensor2D<float> t8 = t7*t7;
    cout<<t8<<endl;
    t8.minus(t7);
    cout<<t8<<endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
