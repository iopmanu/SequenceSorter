#include <iostream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

int main() {
    int array[] = {1, 2, 3, 4, 5};
    /*auto source = new array_sequence<int>(array, 5);
    source->prepend(6);
    source->insert(7, 2);
    source->append(10);
    source->append(20);
    source->append(30);
    source->prepend(40);
    source->insert(50, 5);
    std::cout << source;
    source->erase(3);
    std::cout << source;
    source->erase(5);
    std::cout << source;
    source->erase(6);
    std::cout << source << std::endl << source->get_size();
    source->pop_back();
    source->insert(1000, 200);
    std::cout << std::endl << source << " " << source->get_first() << " " << source->get_last();
    source->clear();
    */

    auto source = new list_sequence<int>(array, 5);
    source->prepend(10);
    source->append(20);
    source->insert(40, 1);
    source->append(50);
    source->prepend(30);
    source->insert(70, 3);
    std::cout << source << " " << " "  << source->get_size() << " " << source->get_first() << " " << source ->get_last();
    
    return 0;
}
