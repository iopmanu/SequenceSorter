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

    template <class Contain, typename T>
    static Contain *shaker_sort(Contain *source, bool (*cmpf)(T, T)) {
        assert(source != NULL);

        std::size_t control = source->get_size() - 1, left = 0,
                    right = source->get_size() - 1;

        do {
            for (std::size_t i = left; i < right; i++) {
                if (cmpf(source->operator[](i), source->operator[](i + 1))) {
                    swap(source->operator[](i), source->operator[](i + 1));
                    control = i;
                }
            }

            right = control;

            for (std::size_t i = right; i > left; i--) {
                if (cmpf(source->operator[](i - 1), source->operator[](i))) {
                    swap(source->operator[](i - 1), source->operator[](i));
                    control = i;
                }
            }

            left = control;
        } while (left < right);

        return source;
    }
};

bool compare_int(int first, int other) { return first > other; }

#endif  // SRC_ISORTER_HPP_
