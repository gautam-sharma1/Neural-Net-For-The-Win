//
// Created by Gautam Sharma on 7/22/21.
//

#include <vector>
#include <iostream>
#include <initializer_list>

#ifndef NNFTW_TENSOR_H
#define NNFTW_TENSOR_H



template<class T>
class Tensor{
public:
    /*
     * Just used for testing. Do not use in production
     */
    Tensor() = default;
    Tensor(std::initializer_list<T> const & tensor):tensor_(tensor){};


private:
    explicit Tensor(std::vector<T> const & tensor){
        std::copy(tensor.begin(), tensor.end(), std::back_inserter(tensor_));
    }

//    Tensor multiply();
public:
    Tensor& plus(const Tensor &other); // performs addition inplace
    Tensor operator+(const Tensor &other);
    //Tensor& operator-(Tensor &other);

//    Tensor operator*(Tensor &other);
     [[nodiscard]] size_t size() const noexcept;

    /*
     * Just a way to access the private member "tensor_"
     * Can think of it as a getter method :)
    */
    const std::vector<T>& operator ()() const;

    const T& operator[](int idx)const{
        return this->tensor_.at(idx);
    }
    Tensor& operator = (const Tensor &other);

    inline bool operator == (Tensor &rhs) const;

    inline bool operator != (Tensor &rhs) const;

    /*
     * Different template argument T1 since ostream is a friend and not part of the Tensor class
     */
    template<class T1>
    friend std::ostream& operator<<(std::ostream& os, Tensor<T1> &t1);


public:

    std::vector<T> tensor_;
};





/*
 *
 * Tensor class definition
 *
 */

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

template<class T>
size_t Tensor<T>::size() const noexcept {
    return tensor_.size();
}

/*
 * Returns a new vector
 */
template<class T>
Tensor<T> Tensor<T>::operator+(const Tensor &other) {
    /*
     * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
     *  broadcasting
     */
    std::vector<T> dest(this->tensor_.begin(), this->tensor_.end());

    if(other.size() > 1 ) {
        assert(other.size() == this->size());
        std::transform (this->tensor_.begin(), this->tensor_.end(), other().begin(), dest.begin(), std::plus<T>());
    }

        // other is a single element tensor
    else {
        assert(other.size() == 1);
        std::for_each(dest.begin(), dest.end(), [&other](T& d) { d+=other().front();});
    }

    return Tensor<T>(dest);
}

template<class T>
Tensor<T> &Tensor<T>::operator=(const Tensor &other) {
    this->tensor_(other());
    return *this;
}

template<class T>
bool Tensor<T>::operator==(Tensor &rhs) const {
    return (this->size() == rhs().size() &&
            std::equal(this->tensor_.begin(), this->tensor_.end(), rhs().begin()));
}

template<class T>
const std::vector<T> &Tensor<T>::operator()() const {
    return this->tensor_;
}

template<class T>
Tensor<T>& Tensor<T>::plus(const Tensor &other) {

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

template<class T>
bool Tensor<T>::operator!=(Tensor &rhs) const {
    return !(*this == rhs);
}

#endif //NNFTW_TENSOR_H
