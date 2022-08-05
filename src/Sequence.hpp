#ifndef SRC_SEQUENCE_HPP_
#define SRC_SEQUENCE_HPP_

#include <cstddef>

template <typename T>
class sequence {
    virtual inline std::size_t get_size() const = 0;
    virtual int find(T) = 0;

    virtual bool empty() = 0;

    virtual void clear() = 0;
    virtual void append(T) = 0;
    virtual void prepend(T) = 0;
    virtual void insert(T, int) = 0;
};

#endif  //SRC_SEQUENCE_HPP_
