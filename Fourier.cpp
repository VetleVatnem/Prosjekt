#pragma once
#include <Fourier.h>
#include <cmath>

Matrix<std::complex<double>> DFT(int size){
    Matrix<std::complex<double>> matrise(size , 0);
    matrise[0][0] = 1;
    double pi = 3.14159265358979323846;

    for (auto i = 0 ; i < size ; i++){
        for (auto j = 0 ; j < size ; j++){
            matrise[i][j] = (1.0/size)*exp(std::complex<double>(0 ,(-2*pi*i*j)/size));
        }
    }
    return matrise;
}