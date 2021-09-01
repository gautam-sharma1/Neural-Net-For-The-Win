//
// Created by Gautam Sharma on 7/22/21.
//

#include <vector>
#include <iostream>
#include <initializer_list>
#include "Utility.h"
#include "Directives.h"
#ifndef NNFTW_TENSOR_H
#define NNFTW_TENSOR_H


namespace NNFTW {

    template<class T>
    class Tensor {
    public:
        /*
         * Just used for testing. Do not use in production
         */
        Tensor() noexcept = default;

        Tensor(const size_t &prealloc) noexcept: tensor_(prealloc) {};

        Tensor(const Tensor &other) noexcept: tensor_(other()) {//std::cout<<"Copy constructor executed"<<std::endl;
        };

        Tensor(const std::initializer_list<T> &tensor) noexcept: tensor_(
                tensor) {//std::cout<<"Init constructor executed"<<std::endl;
        };

        Tensor(const Tensor &&rhs) noexcept: tensor_(
                std::move(rhs())) {//std::cout<<"Move constructor executed"<<std::endl;
        };

        explicit Tensor(std::vector<T> const &tensor) {
            std::copy(tensor.begin(), tensor.end(), std::back_inserter(tensor_));
        }

    private:


//    Tensor multiply();
    public:
        Tensor &multiply(const Tensor &other) {
            __ASSERT__(other.size() == this->size());
            std::transform(this->tensor_.begin(), this->tensor_.end(), other().begin(), this->tensor_.begin(),
                           std::multiplies<T>());
            return *this;
        }

        Tensor operator*(const Tensor &other) {
            __ASSERT__(other.size() == this->size());
            std::vector<T> dest(this->tensor_.begin(), this->tensor_.end());
            std::transform(this->tensor_.begin(), this->tensor_.end(), other().begin(), dest.begin(),
                           std::multiplies<T>());
            return Tensor<T>(dest);
        }

        Tensor &plus(const Tensor &other); // performs addition inplace

        // TODO:
        /*
         * wrapper to reuse for addition and subtraction
         */
        Tensor addOrSubtractByCopy(const Tensor &other, operation op) {
            std::vector<T> dest(this->tensor_.begin(), this->tensor_.end());
            if (other.size() > 1) {
                __ASSERT__(other.size() == this->size());
                if (op == operation::ADD) {
                    std::transform(this->tensor_.begin(), this->tensor_.end(), other().begin(), dest.begin(),
                                   std::plus<T>());
                } else {
                    std::transform(this->tensor_.begin(), this->tensor_.end(), other().begin(), dest.begin(),
                                   std::minus<T>());
                }

            }
                // other is a single element tensor
            else {
                __ASSERT__(other.size() == 1);
                if (op == operation::ADD) {
                    std::for_each(dest.begin(), dest.end(), [&other](T &d) { d += other().front(); });
                } else {
                    std::for_each(dest.begin(), dest.end(), [&other](T &d) { d -= other().front(); });
                }
            }
            return Tensor<T>(dest);
        }

        Tensor &addOrSubtractInPlace(const Tensor &other, operation op) {
            if (other.size() > 1) {
                __ASSERT__(other.size() == this->size());
                if (op == operation::ADD) {
                    std::transform(this->tensor_.begin(), this->tensor_.end(), other().begin(), this->tensor_.begin(),
                                   std::plus<T>());
                } else {
                    std::transform(this->tensor_.begin(), this->tensor_.end(), other().begin(), this->tensor_.begin(),
                                   std::minus<T>());
                }
            }

                // other is a single element tensor
            else {
                __ASSERT__(other.size() == 1);
                if (op == operation::ADD) {
                    std::for_each(this->tensor_.begin(), this->tensor_.end(), [&other](T &d) { d += other().front(); });
                } else {
                    std::for_each(this->tensor_.begin(), this->tensor_.end(), [&other](T &d) { d -= other().front(); });
                }
            }

            return *this;
        }

        Tensor &minus(const Tensor &other);

        Tensor operator+(const Tensor &other);

        Tensor operator-(const Tensor &other);

//    Tensor operator*(Tensor &other);
        __NO_DISCARD__ size_t size() const noexcept;

        /*
         * Just a way to access the private member "tensor_"
         * Can think of it as a getter method :)
        */
        const std::vector<T> &operator()() const;

        /*
         * returns element at index idx
         */
        const T &operator[](int idx) const {
            return this->tensor_.at(idx);
        }

        Tensor &operator=(const Tensor &other);

        inline bool operator==(Tensor &rhs) const;

        inline bool operator!=(Tensor &rhs) const;

        /*
         * Different template argument T1 since ostream is a friend and not part of the Tensor class
         */
        template<class T1>
        friend std::ostream &operator<<(std::ostream &os, Tensor<T1> &t1);


    public:

        std::vector<T> tensor_;
    };


/*
 *
 * Tensor class definition
 *
 */

    template<class T1>
    std::ostream &operator<<(std::ostream &os, Tensor<T1> &input) {
        os << "Tensor{ ";
        for (size_t i = 0; i < input().size() - 1; i++) {
            os << input()[i] << ",";
        }

        os << input().back() << " ";
        os << "}" << std::endl;

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
        return this->addOrSubtractByCopy(other, operation::ADD);
    }

/*
 * Returns a new vector
 */
    template<class T>
    Tensor<T> Tensor<T>::operator-(const Tensor &other) {
        /*
         * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
         *  broadcasting
         */
        return this->addOrSubtractByCopy(other, operation::SUBTRACT);
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
    Tensor<T> &Tensor<T>::plus(const Tensor &other) {
        return this->addOrSubtractInPlace(other, operation::ADD);
    }

    template<class T>
    Tensor<T> &Tensor<T>::minus(const Tensor &other) {
        return this->addOrSubtractInPlace(other, operation::SUBTRACT);
    }

    template<class T>
    bool Tensor<T>::operator!=(Tensor &rhs) const {
        return !(*this == rhs);
    }


}; //eof namespace NNFTW
#endif //NNFTW_TENSOR_H
