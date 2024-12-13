#include <iostream>
#include <cassert>
#include "ring_buffer.hpp"

void test_default_constructor() {
    CircularBuffer buffer;
    assert(buffer.size() == 0);
    assert(buffer.empty());
}

void test_copy_constructor() {
    CircularBuffer buffer1(5, 'A');
    CircularBuffer buffer2(buffer1);
    assert(buffer2.size() == 5);
    for (int i = 0; i < buffer2.size(); ++i) {
        assert(buffer2[i] == 'A');
    }
}

void test_capacity_constructor() {
    CircularBuffer buffer(5);
    assert(buffer.size() == 0);
    assert(buffer.capacity() == 5);
}

void test_capacity_and_element_constructor() {
    CircularBuffer buffer(5, 'A');
    assert(buffer.size() == 5);
    for (int i = 0; i < buffer.size(); ++i) {
        assert(buffer[i] == 'A');
    }
}

void test_index_operator() {
    CircularBuffer buffer(5, 'A');
    buffer[1] = 'B';
    assert(buffer[1] == 'B');
}

void test_at_method() {
    CircularBuffer buffer(5, 'A');
    assert(buffer.at(1) == 'A');
    try {
        buffer.at(5);
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(true);
    }
}

void test_front_back_methods() {
    CircularBuffer buffer(5, 'A');
    assert(buffer.front() == 'A');
    buffer.push_back('B');
    assert(buffer.back() == 'B');
}

void test_linearize_method() {
    CircularBuffer buffer(5, 'A');
    buffer.push_back('B');
    buffer.push_back('C');
    buffer.linearize();
    assert(buffer.front() == 'A');
    assert(buffer.back() == 'C');
}

void test_set_capacity_method() {
    CircularBuffer buffer(5, 'A');
    buffer.set_capacity(10);
    assert(buffer.capacity() == 10);
    buffer.push_back('B');
    buffer.push_back('C');
    assert(buffer.size() == 7); 
}

void test_resize_method() {
    CircularBuffer buffer(5, 'A');
    buffer.resize(7, 'B');
    assert(buffer.size() == 7);
    assert(buffer.capacity() == 7);
    assert(buffer[5] == 'B');
}

void test_push_back_method() {
    CircularBuffer buffer(5);
    buffer.push_back('A');
    assert(buffer.size() == 1);
    assert(buffer[0] == 'A');
}

void test_push_front_method() {
    CircularBuffer buffer(5);
    buffer.push_front('A');
    assert(buffer.size() == 1);
    assert(buffer.front() == 'A');
}

void test_pop_back_method() {
    CircularBuffer buffer(5, 'A');
    buffer.pop_back();
    assert(buffer.size() == 4);
}

void test_pop_front_method() {
    CircularBuffer buffer(5, 'A');
    buffer.pop_front();
    assert(buffer.size() == 4);
    assert(buffer.front() == 'A');
}

void test_insert_method() {
    CircularBuffer buffer(5, 'A');
    buffer.insert(2, 'B');
    assert(buffer.size() == 5);
    assert(buffer[2] == 'B');
}

void test_erase_method() {
    CircularBuffer buffer(5, 'A');
    buffer.erase(1, 3);
    assert(buffer.size() == 3);
}

void test_clear_method() {
    CircularBuffer buffer(5, 'A');
    buffer.clear();
    assert(buffer.size() == 0);
    assert(buffer.empty());
}

void test_comparison_operators() {
    CircularBuffer buffer1(5, 'A');
    CircularBuffer buffer2(5, 'A');
    assert(buffer1 == buffer2);
    buffer2.push_back('B');
    assert(buffer1 != buffer2);
}

int main() {
    test_default_constructor();
    test_copy_constructor();
    test_capacity_constructor();
    test_capacity_and_element_constructor();
    test_index_operator();
    test_at_method();
    test_front_back_methods();
    test_linearize_method();
    test_set_capacity_method();
    test_resize_method();
    test_push_back_method();
    test_push_front_method();
    test_pop_back_method();
    test_pop_front_method();
    test_insert_method();
    test_erase_method();
    test_clear_method();
    test_comparison_operators();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}