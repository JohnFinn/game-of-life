#pragma once

template <typename T>
struct Array3D {
    T* ptr;
    size_t X, Y, Z;

    Array3D(size_t X, size_t Y, size_t Z) : X(X), Y(Y), Z(Z) {
        ptr = new T[X*Y*Z];
    }

    ~Array3D(){
        delete[] ptr;
    }

    T get(size_t x, size_t y, size_t z) {
        return ptr[x*X*Z + y*Z + z];
    }

    void set(size_t x, size_t y, size_t z, T value) {
        ptr[x*X*Z + y*Z + z] = value;
    }

    T* data() {
        return ptr;
    }

    size_t len() {
        return X * Y * Z;
    }
};
