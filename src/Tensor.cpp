//
// Created by Gautam Sharma on 7/22/21.
//

#include "Tensor.h"
// TODO : constructed completed

//using namespace std;
//
//
//
//using namespace NNFTW;
//
//
//
//template<class T1>
//std::ostream & operator<<(std::ostream &os, Tensor<T1> &input) {
//    os << "Tensor{ ";
//    for (size_t i = 0; i < input().size() - 1; i++) {
//        os << input()[i] << ",";
//    }
//
//    os << input().back() << " ";
//    os << "}" << std::endl;
//
//    return os;
//}
//
//template<class T>
//size_t Tensor<T>::size() const noexcept {
//    return tensor_.size();
//}
//
///*
// * Returns a new vector
// */
//template<class T>
//Tensor<T> Tensor<T>::operator+(const Tensor &other) {
//    /*
//     * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
//     *  broadcasting
//     */
//    return this->addOrSubtractByCopy(other, operation::ADD);
//}
//
///*
// * Returns a new vector
// */
//template<class T>
//Tensor<T> Tensor<T>::operator-(const Tensor &other) {
//    /*
//     * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
//     *  broadcasting
//     */
//    return this->addOrSubtractByCopy(other, operation::SUBTRACT);
//}
//
//
//template<class T>
//Tensor<T> &Tensor<T>::operator=(const Tensor &other) {
//    this->tensor_(other());
//    return *this;
//}
//
//
//template<class T>
//bool Tensor<T>::operator==(Tensor &rhs) const {
//    return (this->size() == rhs().size() &&
//            std::equal(this->tensor_.begin(), this->tensor_.end(), rhs().begin()));
//}
//
//template<class T>
//const std::vector<T> &Tensor<T>::operator()() const {
//    return this->tensor_;
//}
//
//template<class T>
//Tensor<T> &Tensor<T>::plus(const Tensor &other) {
//
//    return this->addOrSubtractInPlace(other, operation::ADD);
//
//}
//
//template<class T>
//Tensor<T> &Tensor<T>::minus(const Tensor &other) {
//    return this->addOrSubtractInPlace(other, operation::SUBTRACT);
//}
//
//template<class T>
//bool Tensor<T>::operator!=(Tensor &rhs) const {
//    return !(*this == rhs);
//}
//
//

//namespace NNFTW{
//    template class Tensor<int> ;
//    template class Tensor<float>;
//    template class Tensor<double>;
//}
