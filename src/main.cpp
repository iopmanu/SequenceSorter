#include <iostream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Isorter.hpp"
#include "clocking.hpp"

int main() {
    int array[] = {5, 4, 3, 2, 1};
    
    auto source = new array_sequence<int>(array, 5);
    
    std::cout << "Please input sort type\n";
    std::string desision;
    std::cin >> desision;

    clocking_sorts(source, compare_int, desision);
    return 0;
}
