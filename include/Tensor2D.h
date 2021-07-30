//
// Created by Gautam Sharma on 7/27/21.
//

#ifndef NNFTW_Tensor2D2D_H
#define NNFTW_Tensor2D2D_H
#include <vector>
#include <iostream>
#include <initializer_list>
#include "Tensor.h"


template<class T>
class Tensor2D{
public:
    /*
     * Just used for testing. Do not use in production
     */
    Tensor2D() = default;
    Tensor2D(std::initializer_list<Tensor<T>> const & tensor2D):tensor2D_(tensor2D){};
    template<class T1>
    friend std::ostream& operator<<(std::ostream& os, Tensor2D<T1> &t1);




public:

    std::vector<Tensor<T>> tensor2D_;
};

template<class T1>
std::ostream& operator<<(std::ostream& os, Tensor2D<T1> &input)
{

}


#endif //NNFTW_Tensor2D2D_H
