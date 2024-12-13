#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

typedef char value_type;

class CircularBuffer {

private:
    std::vector<value_type> buffer;
    int start, end, count, buf_capacity;

public:
    CircularBuffer() : start(0), end(0), count(0), buf_capacity(0) {}
    
    ~CircularBuffer() {}

    CircularBuffer(const CircularBuffer &cb)
        : buffer(cb.buffer), start(cb.start), end(cb.end), count(cb.count), buf_capacity(cb.buf_capacity) {}

    explicit CircularBuffer(int capacity)
        : buffer(capacity), start(0), end(0), count(0), buf_capacity(capacity) {}

    CircularBuffer(int capacity, const value_type &elem)
        : buffer(capacity, elem), start(0), end(0), count(capacity), buf_capacity(capacity) {}

    value_type &operator[](int i) {
        return buffer[(start + i) % buf_capacity];
    }

    const value_type &operator[](int i) const {
        return buffer[(start + i) % buf_capacity];
    }

    value_type &at(int i) {
        if (i < 0 || i >= count) throw std::out_of_range("Index out of range");
        return buffer[(start + i) % buf_capacity];
    }

    const value_type &at(int i) const {
        if (i < 0 || i >= count) throw std::out_of_range("Index out of range");
        return buffer[(start + i) % buf_capacity];
    }

    value_type &front() { return buffer[start]; }
    value_type &back() { return buffer[(end - 1 + buf_capacity) % buf_capacity]; }
    const value_type &front() const { return buffer[start]; }
    const value_type &back() const { return buffer[(end - 1 + buf_capacity) % buf_capacity]; }

    value_type* linearize() {
        if (start <= end) {
            return &buffer[start];
        } else {
            std::vector<value_type> temp(count);
            int j = 0;
            for (int i = start; i < buf_capacity; ++i) {
                temp[j++] = buffer[i];
            }
            for (int i = 0; i < end; ++i) {
                temp[j++] = buffer[i];
            }
            std::swap(buffer, temp);
            start = 0;
            end = count;
            return &buffer[start];
        }
    }

    bool is_linearized() const {
        return start <= end;
    }

    void rotate(int new_begin) {
        std::rotate(buffer.begin(), buffer.begin() + new_begin, buffer.end());
        start = new_begin;
        end = (start + count) % buf_capacity;
    }

    int size() const { return count; }
    bool empty() const { return count == 0; }
    bool full() const { return count == buf_capacity; }
    int reserve() const { return buf_capacity - count; }
    int capacity() const { return buf_capacity; }

    void set_capacity(int new_capacity) {
        if (new_capacity < count) throw std::invalid_argument("New capacity cannot be less than current size");
        buffer.resize(new_capacity);
        buf_capacity = new_capacity;
    }

    void resize(int new_size, const value_type &item = value_type()) {
        if (new_size < count) {
            end = (start + new_size) % buf_capacity;
            count = new_size;
        } else if (new_size > buf_capacity) {
            set_capacity(new_size);
        }
        std::fill(buffer.begin() + count, buffer.begin() + new_size, item);
        count = new_size;
        end = (start + count) % buf_capacity;
    }

    CircularBuffer &operator=(const CircularBuffer &cb) {
        if (this != &cb) {
            buffer = cb.buffer;
            start = cb.start;
            end = cb.end;
            count = cb.count;
            buf_capacity = cb.buf_capacity;
        }
        return *this;
    }

    void swap(CircularBuffer &cb) {
        std::swap(buffer, cb.buffer);
        std::swap(start, cb.start);
        std::swap(end, cb.end);
        std::swap(count, cb.count);
        std::swap(buf_capacity, cb.buf_capacity);
    }

    void push_back(const value_type &item = value_type()) {
        if (full()) {
            start = (start + 1) % buf_capacity;
        }
        buffer[end] = item;
        end = (end + 1) % buf_capacity;
        count = std::min(count + 1, buf_capacity);
    }

    void push_front(const value_type &item = value_type()) {
        if (full()) {
            end = (end - 1 + buf_capacity) % buf_capacity;
        }
        start = (start - 1 + buf_capacity) % buf_capacity;
        buffer[start] = item;
        count = std::min(count + 1, buf_capacity);
    }

    void pop_back() {
        if (empty()) throw std::underflow_error("Buffer is empty");
        end = (end - 1 + buf_capacity) % buf_capacity;
        --count;
    }

    void pop_front() {
        if (empty()) throw std::underflow_error("Buffer is empty");
        start = (start + 1) % buf_capacity;
        --count;
    }

    void insert(int pos, const value_type &item = value_type()) {
        if (pos < 0 || pos >= count) throw std::out_of_range("Index out of range");
        push_back();
        for (int i = count - 1; i > pos; --i) {
            buffer[(start + i) % buf_capacity] = buffer[(start + i - 1) % buf_capacity];
        }
        buffer[(start + pos) % buf_capacity] = item;    
    }

    void erase(int first, int last) {
        if (first < 0 || last > count || first >= last) throw std::out_of_range("Invalid range");
        for (int i = 0; i < count - last; ++i) {
            buffer[(start + first + i) % buf_capacity] = buffer[(start + last + i) % buf_capacity];
        }
        count -= (last - first);
        end = (start + count) % buf_capacity;
    }

    void clear() {
        start = 0;
        end = 0;
        count = 0;
    }
};

bool operator==(const CircularBuffer &a, const CircularBuffer &b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool operator!=(const CircularBuffer &a, const CircularBuffer &b) {
    return !(a == b);
}