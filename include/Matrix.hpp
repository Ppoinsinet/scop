#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <type_traits>

template<unsigned int N, unsigned int M, class T = int>
class Matrix {
public:
    T data[N * M];

    Matrix() {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = 0;
    }

    Matrix(const Matrix<N, M, T> &ref) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = ref.data[i];
    }

    Matrix(const T tab[N * M]) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = tab[i];
    }

    Matrix<N, M, T> &operator=(const T tab[N * M]) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = tab[i];
        return *this;
    }

    Matrix<N, M, T> &operator=(const Matrix<N, M, T> &ref) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = ref.data[i];
        return *this;
    }

    template <unsigned int A>
    static T getSum(const Matrix<1, A, T> &a, const Matrix<A, 1, T> &b) {
        T r = T();

        for (unsigned int i = 0; i < A; i++)
            r += a.data[i] * b.data[i];
        return r;
    }
    
    Matrix<N, 1, T> getColumn(unsigned int index) const {
        Matrix<N, 1, T> r;

        for (unsigned int i = 0; i < N; i++) {
            r.data[i] = data[index + (M * i)];
        }
        return r;
    }

    Matrix<1, M, T> getRow(unsigned int index) const {
        Matrix<1, M, T> r;

        for (unsigned int i = 0; i < M; i++) {
            r.data[i] = data[(index * M) + i];
        }
        return r;
    }

    template<unsigned int X>
    Matrix<N, X, T> operator*(const Matrix<M, X, T> &ref) const {
        Matrix<N, X, T> r;
        
        for (unsigned int x = 0; x < X; x++) {
        
            for (unsigned int y = 0; y < M; y++) {

                r.data[(y * X) + x] = getSum(getRow(y), ref.getColumn(x));
            }
        }
        return r;
    }

    void setData(const T val[N * M]) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = val[i];
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<N, M, T>& a) {
        for (unsigned int i = 0; i < N * M; i++) {

            if (i && !(i % M))
                os << "\n";
            os << a.data[i] << " ";
        }
        os << "\n";
        return os;
    }
};

#endif