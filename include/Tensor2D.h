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
    Tensor2D(const Tensor2D & tensor):tensor2D_(tensor()){
        this->rows_ = tensor2D_.size();
        this->cols_ = tensor2D_.at(0).size();
        std::cout<<"2D copy"<<std::endl;
    };
    Tensor2D(const Tensor2D &&tensor) noexcept:tensor2D_(std::move(tensor()))
    {
//        auto tensor_to_move_shape = tensor().size();
//        tensor2D_(tensor_to_move_shape.first_dimension, Tensor<T> (tensor_to_move_shape.second_dimension,0));
//        tensor2D_(std::move(tensor()));
        this->rows_ = tensor2D_.size();
        this->cols_ = tensor2D_.at(0).size();

        std::cout<<"2D move"<<std::endl;};
    // TODO: check size for each individual tensors
    Tensor2D(std::initializer_list<Tensor<T>> const & tensor2D):tensor2D_(tensor2D){
        std::cout<<"2D init"<<std::endl;
        this->rows_ = tensor2D_.size();
        this->cols_ = tensor2D_.at(0).size();
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
            Tensor<T> temp2 = other()[r]; // rth Tensor<T>
            Tensor<T> temp_result = temp1 + temp2;
            result.push_back(temp_result);
        }

        return Tensor2D<T>(result);
    }

    /*
    * Returns a new vector
    * NOTE: Purposely not returned by reference :)
    */
    Tensor2D<T> operator-(const Tensor2D &other) {
        /*
         * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
         * broadcasting
         */
        std::vector<Tensor<T>> result;
        assert(other.size() == this->size());

        for (auto r = 0; r < rows_; r++) {
            Tensor<T> temp1 = this->tensor2D_[r];
            Tensor<T> temp2 = other()[r]; // Tensor<T>
            Tensor<T> temp_result = temp1 - temp2;
            result.push_back(temp_result);
        }

        return Tensor2D<T>(result);
    }
    /*
     *
     */
    Tensor2D transpose(){
        std::vector<Tensor<T>> result;
        for(int i=0; i<this->cols_; i++){
            std::vector<T> temp_vec;
            for(int j=0; j<this->rows_;j++){
                temp_vec.push_back((this->tensor2D_[j][i]));
            }
            result.push_back(std::move(Tensor<T>(temp_vec)));
        }
        return Tensor2D<T>(std::move(result));
    }
    /*
    * Returns a new 2D Tensor
    *
    */
    Tensor2D operator *(const Tensor2D &other){
        assert(other.size().first_dimension == this->size().second_dimension);
        shape s = other.size();
        std::vector<Tensor<T>> result;//(this->size().first_dimension);//,Tensor<T>(s.second_dimension));
        result.reserve(this->size().first_dimension);
        // Matrix multiplication
        for(int i=0; i<this->rows_; i++){
            std::vector<T> temp_vec(s.second_dimension,0);
            for(int j=0; j<this->rows_; j++){
                int temp = 0;
                for(int k=0; k<s.first_dimension; k++){
                    temp += this->tensor2D_[i][k]*other()[k][j];
                }
                temp_vec[j] = temp;
            }

           result.push_back(std::move(Tensor<T>(temp_vec))); // casts vector to a tensor and moves it
        }

        return Tensor2D<T>(std::move(result));

    }
    // TODO:

     /*
     * Modifies in place
     *
    */
    Tensor2D& plus(const Tensor2D &other) {

        assert(other.size() == this->size());

        for (auto r = 0; r < rows_; r++) {
            Tensor<T> &temp1 = this->tensor2D_[r];
            Tensor<T> temp2 = other()[r]; // Tensor<T>
            temp1.plus(temp2);
        }
        return *this;
    }

    Tensor2D& minus(const Tensor2D &other) {

        assert(other.size() == this->size());

        for (auto r = 0; r < rows_; r++) {
            Tensor<T> &temp1 = this->tensor2D_[r];
            Tensor<T> temp2 = other()[r]; // Tensor<T>
            temp1.minus(temp2);
        }

        return *this;

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
    auto input_shape = input.size();
    std::cout<<"Tensor2D {"<<std::endl;
    for(int tensor_idx = 0; tensor_idx <  input_shape.first_dimension; tensor_idx++){
        // TODO: Not efficient to make a new Tensor just to print
        Tensor<float> temp(std::move(input[tensor_idx]));
        os<<temp;
    }
    os<<" }"<<std::endl;
    return os;
}


#endif //NNFTW_Tensor2D2D_H
