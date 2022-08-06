#ifndef SRC_ISORTER_HPP_
#define SRC_ISORTER_HPP_

#include "Sequence.hpp"

template <typename T>
void swap(T &first, T &other) {
    T tmp = first;
    first = other;
    other = tmp;
}

class Isorter {
public:
    template <class Contain, typename T>
    static Contain *bubble_sort(Contain *source, bool (*cmpf)(T, T)) {
        assert(source != NULL);

        for (std::size_t i = 0; i < source->get_size(); i++) {
            for (std::size_t j = 0; j < source->get_size() - i - 1; j++) {
                if (cmpf(source->operator[](j), source->operator[](j + 1)))
                    swap(source->operator[](j), source->operator[](j + 1));
            }
        }

        return source;
    }
};

bool compare_int(int first, int other) { return first > other; }

#endif  // SRC_ISORTER_HPP_
