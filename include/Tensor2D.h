//
// Created by Gautam Sharma on 7/27/21.
//

#ifndef NNFTW_Tensor2D2D_H
#define NNFTW_Tensor2D2D_H
#include <vector>
#include <iostream>
#include <initializer_list>
#include "Utility.h"
#include "Tensor.h"
#include "Constants.h"


template<class T>
class Tensor2D{

public:
    // Just to be used for testing
    explicit Tensor2D(std::vector<Tensor<T>> const & tensor){
        std::copy(tensor.begin(), tensor.end(), std::back_inserter(tensor2D_));
        this->rows_ = tensor2D_.size();
        this->cols_ = tensor2D_.at(0).size();
    }
public:
    /*
     * Just used for testing. Do not use in production
     */
    Tensor2D() = default;

    // TODO: check size for each individual tensors
    Tensor2D(std::initializer_list<Tensor<T>> const & tensor2D):tensor2D_(tensor2D){
        rows_ = tensor2D_.size();
        cols_ = tensor2D_.at(0).size();
    };

    // return rows, columns of the Tensor
    [[nodiscard]] shape size() const noexcept{
        return shape({rows_, cols_});
    }


    /*
    * Just a way to access the private member "tensor_"
    * Can think of it as a getter method :)
    */
    const std::vector<Tensor<T>>& operator ()() const{
        return this->tensor2D_;
    }


    Tensor2D& operator = (const Tensor2D &other){
        this->tensor2D_(other());
        return *this;
    }

    const Tensor<T>& operator[](int idx)const{
        return this->tensor2D_.at(idx);
    }

    bool operator==(const Tensor2D &rhs) const {
        for(auto r = 0; r<rows_; r++){
            Tensor<T> first = this->tensor2D_[r];
            Tensor<T> second = rhs()[r];
            if(first != second){
                return false;
            }
        }
        return true;
    }

    bool operator !=(const Tensor2D &rhs) const{
        return !(*this == rhs);
    }

    /*
    * Returns a new vector
     * NOTE: Purposely not returned by reference :)
    */
    Tensor2D<T> operator+(const Tensor2D &other) {
        /*
         * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
         * broadcasting
         */
        std::vector<Tensor<T>> result;
        assert(other.size() == this->size());

        for (auto r = 0; r < rows_; r++) {
            Tensor<T> temp1 = this->tensor2D_[r];
            Tensor<T> temp2 = other()[r]; // Tensor<T>
            Tensor<T> temp_result = temp1 + temp2;
            result.push_back(temp_result);
        }

        return Tensor2D<T>(result);
    }


     /*
     * Modifies in place
     *
    */
    void  plus(const Tensor2D &other) {

        assert(other.size() == this->size());

        for (auto r = 0; r < rows_; r++) {
            Tensor<T> &temp1 = this->tensor2D_[r];
            Tensor<T> temp2 = other()[r]; // Tensor<T>
            temp1.plus(temp2);
        }

    }



    template<class T1>
    friend std::ostream& operator<<(std::ostream& os, Tensor2D<T1> &t1);





public:

    std::vector<Tensor<T>> tensor2D_;
    size_t rows_;
    size_t cols_;
};

template<class T1>
std::ostream& operator<<(std::ostream& os, Tensor2D<T1> &input)
{

}


#endif //NNFTW_Tensor2D2D_H
