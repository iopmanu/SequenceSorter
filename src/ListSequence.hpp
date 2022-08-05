#ifndef SRC_LIST_SEQUENCE_HPP_
#define SRC_LIST_SEQUENCE_HPP_

#include "Sequence.hpp"

#include <assert.h>
#include <cstddef>
#include <iostream>

template <typename T> struct node {
    T data;
    node* next;

    node(const T& _data, node* _next): data(_data), next(_next) {}
};

template <typename T> class list_sequence {
private:
    node<T>* head = NULL;
    node<T>* tail = NULL;
    std::size_t size;

public:
    /*==================================ITERATORS==================================*/
    class list_iterator {
        node<T>* it;

    public:
        explicit list_iterator(node<T>* _it) noexcept: it(_it) {}

        node<T>* current_ptr() noexcept { return it; }

        void set_next(node<T>* _next) { it->next = _next; }

        const T& get_value() noexcept { return this->it->data; }

        bool operator!=(const list_iterator& to_compare) const noexcept {
            return this->it != to_compare.it;
        }

        list_iterator operator++() noexcept {
            assert(it != NULL);
            it = it->next;
            return *this;
        }
    };

    list_iterator begin() const noexcept { return list_iterator(this->head); }

    list_iterator end() const noexcept {
        return list_iterator(this->tail->next);
    }

    /*==================================INLINE_FUNCTIONS==================================*/
    inline std::size_t get_size() const noexcept { return this->size; }

    inline bool empty() const noexcept { return this->size == 0; }

    inline T& get_first() const {
        assert(!this->empty());
        return this->head->data;
    }

    inline T& get_last() const {
        assert(!this->empty());
        return this->tail->data;
    }

    /*==================================CONSTRUCTORS==================================*/
    explicit list_sequence() noexcept: head(NULL), tail(NULL), size(0) {}

    explicit list_sequence(const T& value):
        head(new node<T>(value, NULL)), size(1) {
        tail = head;
    }

    explicit list_sequence(T* source, std::size_t count) noexcept: size(count) {
        for (std::size_t i = 0; i < count; i++) {
            this->append(source[i]);
        }
    }

    /*==================================OPERATORS==================================*/
    friend std::ostream& operator<<(std::ostream& out,
                                    list_sequence<T>* source) noexcept {
        for (list_iterator iter = source->begin(); iter != source->end();
             iter.operator++()) {
            out << iter.get_value() << " ";
        }
        out << std::endl;

        return out;
    }

    /*==================================METHODS==================================*/
    void append(const T& source) {
        if (this->head == NULL) {
            head = new node<T>(source, NULL);
            tail = head;
            size = 1;
        } else {
            tail->next = new node<T>(source, NULL);
            tail = tail->next;
            size++;
        }
    }

    void prepend(const T& source) {
        if (this->head == NULL) {
            head = new node<T>(source, NULL);
            tail = head;
            size = 1;
        } else {
            auto new_head = new node<T>(source, head);
            head = new_head;
            size++;
        }
    }

    void insert(const T& value, std::size_t index) {
        if (index >= this->size) {
            this->append(value);
            return;
        } else if (index == 0) {
            this->prepend(value);
            return;
        }

        list_iterator slow = this->begin(), fast = (this->begin().operator++());

        for (; fast != this->end() && index > 1;
             slow.operator++(), fast.operator++(), --index)

        (slow.current_ptr())->next = new node<T>(value, fast.current_ptr());
        this->size++;
    }
};

#endif // SRC_LIST_SEQUENCE_HPP_
