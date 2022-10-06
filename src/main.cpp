#include <iostream>

#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Isorter.hpp"
#include "clocking.hpp"
#include "testing.hpp"

int main() {
    if (test_bubble() || test_merge() || test_shaker()) {
        std::cout << "TESTS FAILED";
    }

    //int array[] = {5, 4, 3, 2, 1};
    auto source = new list_sequence<int>();
    std::cout << "Please input sort type\n";
    std::string desision;
    std::cin >> desision;

    clocking_sorts(source, compare_int, desision);
    
    delete source;
    return 0;
}
