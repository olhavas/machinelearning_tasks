//
// Created by Olha Vasylyshyn on 2/3/2021.
//

#ifndef PROGRAM_TRAINER_H
#define PROGRAM_TRAINER_H

#include <regex>
#include <string>
#include <iomanip>

template<typename T>
std::vector<T> multiply(std::vector<T> A, std::vector<T> B) {
    std::vector<T> C;
    assertm(A.size() == B.size(), "VECTORS OF MULTIPLY FUNCTIONS HAS TO BE THE SAME SIZE!");
    for ( auto i = 0; i < A.size(); i++ ) {
        C.push_back(A[i] * B[i]);
    }
    return C;
}

template<typename T>
std::vector<T> substract(std::vector<T> A, std::vector<T> B) {
    std::vector<T> C;
    assertm(A.size() == B.size(), "VECTORS OF SUBSTRACT FUNCTIONS HAS TO BE THE SAME SIZE!");
    for ( auto i = 0; i < A.size(); i++ ) {
        C.push_back(A[i] - B[i]);
    }
    return C;
}

template<typename T>
T sum(std::vector<T> A) {
    T sum = static_cast<T>(0.0);
    for ( auto i = 0; i < A.size(); i++ ) {
        sum += A[i];
    }
    return sum;
}

template<typename T>
std::vector<T> power(std::vector<T> A, T number) {
    std::vector<T> C;
    for ( auto i = 0; i < A.size(); i++ ) {
        T pow = static_cast<T>(1.0);
        for (auto j=0;j< number;j++ ) {
            pow *= A[i];
        }
        C.push_back(pow);
    }
    return C;
}

template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &cols) {
    if (cols.size() == 0)
        return cols;
    std::vector<std::vector<T>> C(cols[0].size(), std::vector<T>());

    for ( int i = 0; i < cols.size(); i++ ) {
        for ( int j = 0; j < cols[i].size(); j++ ) {
            C[j].push_back(cols[i][j]);
        }
    }
    return C;
}

#endif //PROGRAM_TRAINER_H
