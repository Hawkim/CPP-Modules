#ifndef ITER_HPP
#define ITER_HPP

template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
const T &min(const T &a, const T &b) {
    if (b < a) {
        return b;
    }
    return a;
}

template <typename T>
const T &max(const T &a, const T &b) {
    if (b > a) {
        return b;
    }
    return a;
}

#endif