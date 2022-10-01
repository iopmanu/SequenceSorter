#include <iostream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Isorter.hpp"
#include "clocking.hpp"

int main() {
    int array[] = {1,3,5,6,8,2,4,7,9,10};
    
    auto source = new list_sequence<int>(array, 10);
    std::cout << source;
    Isorter_list::merge_sort_list(source, compare_int);

    std::cout << source;

    delete source;

    /*auto source = new array_sequence<int>(array, 5);
    std::cout << "Please input sort type\n";
    std::string desision;
    std::cin >> desision;

    clocking_sorts(source, compare_int, desision); */
    return 0;
}
