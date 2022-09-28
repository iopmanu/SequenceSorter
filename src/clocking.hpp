#include "Isorter.hpp"
#include <chrono>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace std::chrono;

bool is_bubble(const std::string &sort_type) { return sort_type == "bubble"; }

bool is_shaker(const std::string &sort_type) { return sort_type == "shaker"; }

bool is_quick(const std::string &sort_type) { return sort_type == "quick"; }

bool is_merge(const std::string &sort_type) { return sort_type == "merge"; }

template <class Contain>
void randomize_container_int(Contain *source) {
    srand(time(NULL));
    for (std::size_t i = 0; i < 10000; i++) {
        source->append(1 + rand() % RAND_MAX);
    }
}

template <class Contain, typename T>
void clocking_sorts(Contain *source, bool (*cmpf)(T, T),
                    const string &sort_type) {
    randomize_container_int(source);

    auto start_clock = high_resolution_clock::now();

    if (is_bubble(sort_type)) {
        Isorter::bubble_sort(source, cmpf);
    } else if (is_shaker(sort_type)) {
        Isorter::shaker_sort(source, cmpf);
    } else if (is_quick(sort_type)) {
        Isorter::qsort(source, cmpf, 0, source->get_size() - 1);
    } else if (is_merge(sort_type)) {
        Isorter::merge_sort(source, cmpf, 0, source->get_size() - 1);
    } else {
        std::cout << "Неадекватный ввод!";
    }

    auto stop_clock = high_resolution_clock::now();
    auto duration = stop_clock - start_clock;

    std::cout << "Duration is: " << duration.count();
}
