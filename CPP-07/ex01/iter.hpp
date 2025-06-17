#ifndef ITER_HPP
#define ITER_HPP

// Forward declaration of print function template
template<typename T>
void print(T const &x);

// Special resolver function for print
template<typename T>

void (*print_resolver(T const &))(T const &) {
    return &print<T>;
}

template <typename T>
void iter(T* array, size_t length, void (*function)(T const &)) {
    for (size_t i = 0; i < length; ++i) {
        function(array[i]);
    }
}

#endif