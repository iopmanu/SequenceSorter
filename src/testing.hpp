#ifndef SRC_TESTING_HPP__
#define SRC_TESTING_HPP__

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <stdlib.h>
#include <vector>

#include "ArraySequence.hpp"
#include "Isorter.hpp"
#include "ListSequence.hpp"

bool test_bubble();
bool test_shaker();
bool test_merge();

enum test_status {
    SUCCES = 0,
    ERROR = 1,
};

template <typename T1, typename T2>
bool equal(const T1& first, const T2& second) {
    // assert(first == second);
    if (first != second)
        return ERROR;
    else
        return SUCCES;
}

bool test_bubble() {
    srand(time(NULL));

    vector<int> v;
    for (std::size_t i = 0; i < 1000; i++) {
        v.push_back(1 + rand() % RAND_MAX);
    }

    auto sequence = new array_sequence<int>(4);
    for (std::size_t i = 0; i < 1000; i++) {
        sequence->append(v[i]);
    }

    std::sort(v.begin(), v.end());
    sequence = Isorter::bubble_sort(sequence, compare_int);

    for (std::size_t i = 0; i < 1000; i++) {
        if (equal(v[i], sequence->operator[](i))) return ERROR;
    }

    return SUCCES;
}

bool test_shaker() {
    srand(time(NULL));

    vector<int> v;
    for (std::size_t i = 0; i < 1000; i++) {
        v.push_back(1 + rand() % RAND_MAX);
    }

    auto sequence = new array_sequence<int>(4);
    for (std::size_t i = 0; i < 1000; i++) {
        sequence->append(v[i]);
    }

    std::sort(v.begin(), v.end());
    sequence = Isorter::shaker_sort(sequence, compare_int);

    for (std::size_t i = 0; i < 1000; i++) {
        if (equal(v[i], sequence->operator[](i))) return ERROR;
    }

    return SUCCES;
}

bool test_merge() {
    srand(time(NULL));

    vector<int> v;
    for (std::size_t i = 0; i < 1000; i++) {
        v.push_back(1 + rand() % RAND_MAX);
    }

    auto sequence = new array_sequence<int>(4);
    for (std::size_t i = 0; i < 1000; i++) {
        sequence->append(v[i]);
    }

    std::sort(v.begin(), v.end());
    Isorter::merge_sort(sequence, compare_int, 0, sequence->get_size() - 1);

    for (std::size_t i = 0; i < 1000; i++) {
        if (equal(v[i], sequence->operator[](i))) return ERROR;
    }

    return SUCCES;
}

#endif  // SRC_TESTING_HPP__
