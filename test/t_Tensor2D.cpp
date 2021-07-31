//
// Created by Gautam Sharma on 7/27/21.
//

#include <iostream>
#include <gtest/gtest.h>
#include <cassert>
#include "Tensor2D.h"
#include "Utility.h"



TEST(GTtest, CanInitializeTensor){
    Tensor<float> t1 ({1,2.555,3,4,5,6.667,7,8});
    Tensor<float> t2({1,2,3,4,5});
    Tensor<float> t3({1,2,3,4,5});
    Tensor2D<float> t4 (   {t1,t2,t3} );
}

TEST(GTtest, CanReturnCorrectTensorSize){
    Tensor<float> t1 ({1,2.555,6.667,7,8});
    Tensor<float> t2({1,2,3,4,5});
    Tensor<float> t3({1,2,3,4,5});
    Tensor2D<float> t4 (   {t1,t2,t3} );
    shape EXPECTED_SIZE = shape({3,5});
    shape ACTUAL_SIZE = t4.size();
    ASSERT_EQ(EXPECTED_SIZE, ACTUAL_SIZE);
}

TEST(GTtest, CanCompareTensor2D){
    Tensor<float> t1 ({1,2.555,-6.667,7,8});
    Tensor<float> t2({11.333,22.56,36.78,94.89,-51.43});
    Tensor<float> t3({11.333,22.56,36.78,94.89,-51.43});

    const Tensor2D<float> t4 (   {t1,t2} );
    const Tensor2D<float> t5 (   {t1,t2} );
    const Tensor2D<float> t6 ({t3,t3});


    ASSERT_EQ(t4, t5);
    ASSERT_NE(t4, t6);
    ASSERT_NE(t5, t6);
}


TEST(GTtest, OverloadSquareBracketOperatorTensor2D){
    Tensor<float> t1 ({-11.10,2.555,-6.667,7,89.99});
    Tensor<float> t2({11.333,222222222.56,32232326.78,9445555.89,-51111111111.43});

    Tensor2D<float> t3 (   {t1,t2} );
    Tensor<float> EXPECTED_SECOND_TENSOR  = t3[1];
    //assert(EXPECTED_SECOND_TENSOR==t2);
    ASSERT_TRUE(EXPECTED_SECOND_TENSOR==t2);
}

TEST(GTtest, CanAddCorrectlyTensor2D){
    Tensor<float> t1 ({1,2,3});
    Tensor<float> t2({3,4,5});
    Tensor<float> t3({3,4});
    /*
     * t3 = t4 =
     * {1,2,3}
     * {3,4,5}
     */
    Tensor2D<float> t4 (   {t1,t2} );
    Tensor2D<float> t5 (   {t1,t2} );

    /*
     * Incorrect dimension
     * EXPECTED to throw error
     */
    Tensor2D<float> t6 (   {t1,t3} );
    /*
     * t3+t4 =
     * {1,4,6}
     * {6,8,10}
     */
    Tensor2D<float> t7 = t4+t5;
    //ASSERT_ANY_THROW(t4 + t6);
}

TEST(GTtest, CanAddCorrectlyInPlaceTensor2D){
    Tensor<float> t1 ({1,2,3});
    Tensor<float> t2({3,4,5});

    /*
     * t3 = t4 =
     * {1,2,3}
     * {3,4,5}
     */
    Tensor2D<float> t4 (   {t1,t2} );
    Tensor2D<float> t5 (   {t1,t2} );


    /*
     * t3+t4 =
     * {1,4,6}
     * {6,8,10}
     */
    auto EXPECTED_TENSOR2D = t4+t5;
    t4.plus(t5);
    ASSERT_TRUE(EXPECTED_TENSOR2D==t4);

}


//TEST(GTtest, CanReturnTensor){
//    Tensor<float> t1 ({1,2.555,-6.667,7,8});
//    Tensor<float> t2({11.333,22.56,36.78,94.89,-51.43});
//    Tensor2D<float> t4 (   {t1,t2} );
//    Tensor2D EXPECTED_TENSOR2D = Tensor2D<float>({t1,t2});
//    Tensor2D ACTUAL_TENSOR2D = t4();
//    ASSERT_EQ(EXPECTED_SIZE, ACTUAL_SIZE);
//}