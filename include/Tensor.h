//
// Created by Gautam Sharma on 7/22/21.
//

#include <vector>
#include <cstdarg>
#include <iostream>
#include <initializer_list>

#ifndef NNFTW_TENSOR_H
#define NNFTW_TENSOR_H



template<class T>
class Tensor {
public:
    /*
     * Just used for testing. Do not use in production
     */
    Tensor() = default;
    Tensor(std::initializer_list<T> const & tensor):tensor_(tensor){};

//    Tensor multiply();
//    Tensor operator+(T);
    Tensor& operator+(Tensor &other){
        /*
         * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
         *  broadcasting
         */
        if(other.size() > 1 ) {
            assert(other.size() == this->size());
            std::transform (this->tensor_.begin(), this->tensor_.end(), other().begin(), this->tensor_.begin(), std::plus<T>());
        }

        // other is a single element tensor
        else {
            assert(other.size() == 1);
            std::for_each(this->tensor_.begin(), this->tensor_.end(), [&other](T& d) { d+=other().front();});
        }

        return *this;
    }
//    Tensor operator-(Tensor &other);
//    Tensor operator*(Tensor &other);
    size_t size() const noexcept{
        return tensor_.size();
    }

    /*
     * Just a way to access the private member "tensor_"
     * Can think of it as a getter method :)
    */
    std::vector<T>& operator ()(){
        return this->tensor_;
    }

    Tensor& operator = (const Tensor &other) const{
        return other;
    }

    inline bool operator == (Tensor &rhs) const {
        return (this->size() == rhs().size() &&
                std::equal(this->tensor_.begin(), this->tensor_.end(), rhs().begin()));
    }

    /*
     * Different template argument T1 since ostream is a friend and not part of the Tensor class
     */
    template<class T1>
    friend std::ostream& operator<<(std::ostream& os, Tensor<T1> &t1);


private:

    std::vector<T> tensor_;
};

template<class T1>
std::ostream& operator<<(std::ostream& os, Tensor<T1> &input)
{
    os << "Tensor{ ";
    for(size_t i = 0; i<input().size()-1; i++){
        os << input()[i] << ",";
    }

    os << input().back()<<" ";
    os<<"}"<<std::endl;

    return os;
}

#endif //NNFTW_TENSOR_H
