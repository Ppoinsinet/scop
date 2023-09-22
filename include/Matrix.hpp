#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <type_traits>

template<unsigned int N, unsigned int M, class T = int>
class Matrix {
public:
    T data[N * M];

    Matrix() {
        for (unsigned int i = 0; i < N * M; i++) {
            data[i] = T();
        }
    }

    Matrix(const Matrix<N, M, T> &ref) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = ref.data[i];
    }

    Matrix(const T tab[N * M]) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] = tab[i];
    }

    static typename std::enable_if<std::is_arithmetic<T>::value, Matrix<N, N, T> >::type Identity() {
        unsigned int step = 0;
        Matrix<N, N, T> r;
        for (unsigned int i = 0; i < M * M; i++) {
            if (i == step) {
                r.data[i] = 1;
                step += 1 + M;
            }
        }
        return r;
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

    Matrix<N, M, T> operator+(const Matrix<N, M, T> &ref) const {
        Matrix<N, M, T> r;

        for (unsigned int i = 0; i < N * M; i++)
            r.data[i] = data[i] + ref.data[i];
        return r;
    }

    Matrix<N, M, T> operator-(const Matrix<N, M, T> &ref) const {
        Matrix<N, M, T> r;

        for (unsigned int i = 0; i < N * M; i++)
            r.data[i] = data[i] - ref.data[i];
        return r;
    }

    Matrix<N, M, T> &operator+=(const Matrix<N, M, T> &ref) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] += ref.data[i];
        return *this;
    }

    Matrix<M, N, T> transpose() {
        Matrix<M, N, T> r;

        for (size_t x = 0; x < N; x++) {

            for (size_t y = 0; y < M; y++) {

                r.data[(x * M) + y] = data[x + (y * M)];
            }
        }
        return r;
    }

    Matrix<N, M, T> &operator-=(const Matrix<N, M, T> &ref) {
        for (unsigned int i = 0; i < N * M; i++)
            data[i] -= ref.data[i];
        return *this;
    }

    template <unsigned int A>
    static T getSum(const Matrix<1, A, T> &row, const Matrix<A, 1, T> &col) {
        T r = T();

        for (unsigned int i = 0; i < A; i++)
            r += row.data[i] * col.data[i];
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
        
            for (unsigned int y = 0; y < N; y++) {

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