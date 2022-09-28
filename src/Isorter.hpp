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

    template <class Contain, typename T>
    static Contain *qsort(Contain *source, bool (*cmpf)(T, T),
                          const std::size_t left, const std::size_t right) {
        assert(source != NULL);

        if (left < right) {
            std::size_t pivot = partition(source, cmpf, left, right);

            qsort(source, cmpf, left, pivot - 1);
            qsort(source, cmpf, pivot + 1, right);
        }

        return source;
    }

    template <class Contain, typename T>
    static std::size_t partition(Contain *source, bool (*cmpf)(T, T),
                                 std::size_t left, std::size_t right) {
        std::size_t i = left, j = left;
        T pivot = source->operator[](right);

        while (i <= right) {
            if (cmpf(source->operator[](i), pivot)) {
                i++;
            } else {
                swap(source->operator[](i), source->operator[](j));
                i++;
                j++;
            }
        }

        return j - 1;
    }

    template <class Contain, typename T>
    static void merge_sort(Contain *source, bool (*cmpf)(T, T),
                           const std::size_t &begin, const std::size_t &end) {
        if (begin >= end) {
            return;
        }

        std::size_t mid = begin + (end - begin) / 2;
        merge_sort(source, cmpf, begin, mid);
        merge_sort(source, cmpf, mid + 1, end);
        merge(source, cmpf, begin, mid, end);
    }

    template <class Contain, typename T>
    static void merge(Contain *source, bool (*cmpf)(T, T), const std::size_t &left,
               const std::size_t &mid, const std::size_t &right) {
        std::size_t first_subarray_length = mid - left + 1;
        std::size_t second_subarray_length = right - mid;

        auto left_subarray = new Contain(first_subarray_length);
        auto right_subarray = new Contain(second_subarray_length);

        for (std::size_t i = 0; i < first_subarray_length; i++) {
            left_subarray->append(source->operator[](left + i));
        }
        for (std::size_t i = 0; i < second_subarray_length; i++) {
            right_subarray->append(source->operator[](mid + i + 1));
        }

        std::size_t index_first_subarray = 0, index_second_subarray = 0,
                    index_merged = left;

        while ((index_first_subarray < first_subarray_length) &&
               (index_second_subarray < second_subarray_length)) {
            if (!cmpf(left_subarray->operator[](index_first_subarray),
                      right_subarray->operator[](index_second_subarray))) {
                source->operator[](index_merged++) =
                    left_subarray->operator[](index_first_subarray++);
            } else {
                source->operator[](index_merged++) =
                    right_subarray->operator[](index_second_subarray++);
            }
        }

        while (index_first_subarray < first_subarray_length) {
            source->operator[](index_merged++) =
                left_subarray->operator[](index_first_subarray++);
        }

        while (index_second_subarray < second_subarray_length) {
            source->operator[](index_merged++) =
                right_subarray->operator[](index_second_subarray++);
        }

        delete left_subarray;
        delete right_subarray;
    }
};

bool compare_int(int first, int other) { return first > other; }

#endif  // SRC_ISORTER_HPP_
