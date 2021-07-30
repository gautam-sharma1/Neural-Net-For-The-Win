//
// Created by Gautam Sharma on 7/27/21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "Tensor2D.h"



TEST(GTtest, CanInitializeTensor){
    Tensor<float> t1 ({1,2.555,3,4,5,6.667,7,8});
    Tensor<float> t2({1,2,3,4,5});
    Tensor<flroat> t3({1,2,3,4,5});
    Tensor2D<float> t4 (   {t1,t2,t3} );
}
