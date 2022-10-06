#ifndef SRC_LIST_SEQUENCE_HPP_
#define SRC_LIST_SEQUENCE_HPP_

#include "Sequence.hpp"

#include <assert.h>
#include <cstddef>
#include <iostream>

#define INIT_SIZE 1

template <typename T>
struct node {
    T data;
    node* next;

    node(const T& _data, node* _next) : data(_data), next(_next) {}
};

template <typename T>
class list_sequence : virtual public sequence<T> {
private:
    node<T>* head = NULL;
    node<T>* tail = NULL;
    std::size_t size;

public:
    /*==================================ITERATORS==================================*/
    class list_iterator {
        node<T>* it;

    public:
        explicit list_iterator(node<T>* _it) noexcept : it(_it) {}

        node<T>* current_ptr() noexcept { return it; }

        T& get_value() noexcept { return this->it->data; }

        void set_ptr(node<T>* _ptr) noexcept { this->it = _ptr; }

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

    list_iterator preend() const noexcept { return list_iterator(this->tail); }

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
    explicit list_sequence() noexcept : head(NULL), tail(NULL), size(0) {}

    explicit list_sequence(const T& value)
        : head(new node<T>(value, NULL)), size(INIT_SIZE) {
        tail = head;
    }

    explicit list_sequence(T* source, std::size_t count) noexcept
        : size(count) {
        for (std::size_t i = 0; i < count; i++) {
            this->append(source[i]);
        }
    }

    explicit list_sequence(node<T>* _head) : head(_head) {
        node<T>* current = _head;

        while (current->next != NULL) {
            this->append(current->data);
            current = current->next;
        }

        this->tail = current;
    }

    /*==================================OPERATORS==================================*/
    friend std::ostream& operator<<(std::ostream& out,
                                    list_sequence<T>* source) noexcept {
        if (source->head == NULL) {
            return out;
        }

        for (list_iterator iter = source->begin(); iter != source->end();
             iter.operator++()) {
            out << iter.get_value() << " ";
        }
        out << std::endl;

        return out;
    }

    inline T& operator[](const std::size_t& index) {
        assert(index < this->size);
        assert(!this->empty());

        list_iterator it = this->begin();

        for (int i = index; i > 0; it.operator++(), i--)
            ;

        return it.get_value();
    }

    /*==================================METHODS==================================*/
    void append(const T& source) {
        if (head == NULL) {
            head = new node<T>(source, NULL);
            tail = head;
            size = INIT_SIZE;
        } else {
            tail->next = new node<T>(source, NULL);
            tail = tail->next;
            ++size;
        }
    }

    void prepend(const T& source) {
        if (this->head == NULL) {
            head = new node<T>(source, NULL);
            tail = head;
            size = INIT_SIZE;
        } else {
            auto new_head = new node<T>(source, head);
            head = new_head;
            size++;
        }
    }

    void set_head(node<T>* _head) {
        this->head = _head;

        node<T>* current = _head;

        while (current->next != NULL) {
            current = current->next;
        }

        this->tail = current;
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
            ;

        (slow.current_ptr())->next = new node<T>(value, fast.current_ptr());
        this->size++;
    }

    void rev_out(node<T>* ptr, bool is_first) {
        if (ptr == nullptr && is_first) {
            rev_out(this->head, false);
        } else if (ptr == nullptr && !is_first) {
            return;
        }

        if (ptr != nullptr) {
            rev_out(ptr->next, false);
        }

        if (ptr != nullptr) {
            std::cout << ptr->data;
        }
    }

    void erase(std::size_t index) {
        if (index == 0) {
            this->erase_first();
            return;
        }

        assert(index < this->size);
        assert(!this->empty());

        list_iterator slow = this->begin(), fast = this->begin().operator++();

        for (; fast != this->end() && index > 1;
             slow.operator++(), fast.operator++(), --index)
            ;

        (slow.current_ptr())->next = (fast.current_ptr())->next;
        this->size--;
    }

    void erase_first() {
        assert(!this->empty());

        this->head = this->head->next;
        this->size--;
    }

    void pop_back() { erase(this->size - 1); }

    std::size_t find(const T& value) noexcept {
        std::size_t pos = 0;
        list_iterator slow = this->begin();

        for (; slow != this->end(); slow.operator++(), pos++) {
            if (slow.get_value() == value) {
                break;
            }
        }

        return pos;
    }

    void clear() noexcept {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }

    ~list_sequence() {
        node<T>* current = this->head;
        node<T>* to_delete = current;

        while (current != NULL) {
            current = current->next;
            delete to_delete;
            to_delete = current;
        }
    }
};

#endif  // SRC_LIST_SEQUENCE_HPP_
