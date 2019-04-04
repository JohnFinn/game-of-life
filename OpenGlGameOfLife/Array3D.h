#pragma once

#include <vector>

template <typename T>
struct Array3D {
    std::vector<T> storage;
    size_t X, Y, Z;

    Array3D(size_t X, size_t Y, size_t Z) : X(X), Y(Y), Z(Z), storage(X*Y*Z) {}

    T get(size_t x, size_t y, size_t z) {
        return storage[x*X*Z + y*Z + z];
    }

    void set(size_t x, size_t y, size_t z, T value) {
        storage[x*X*Z + y*Z + z] = value;
    }

    T* data() {
        return storage.data();
    }

    size_t len() {
        return X * Y * Z;
    }
};
