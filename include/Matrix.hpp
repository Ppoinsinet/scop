#ifndef MATRIX_HPP
#define MATRIX_HPP

template<unsigned int N, class T = int>
class Matrix {
public:
    static const unsigned int n = N;
    T data[N * N];

    Matrix() {
        for (unsigned int i = 0; i < n; i++)
            data[i] = 0;
    }
    Matrix(const Matrix<N, T> &ref) {
        for (unsigned int i = 0; i < n; i++)
            data[i] = ref.data[i];
    }
    Matrix<N, T> &operator=(const Matrix<N, T> &ref) {
        for (unsigned int i = 0; i < n; i++)
            data[i] = ref.data[i];
        return *this;
    }

    void setData(T val[N * N]) {
        for (unsigned int i = 0; i < n; i++)
            data[i] = val[i];
    }
};

#endif