#include <vector>
#include <stdexcept>
#include <algorithm>

typedef char value_type;

class CircularBuffer {
    std::vector<value_type> buffer;
    int start, end, count, buf_capacity;

public:
    // Constructor: Initializes an empty CircularBuffer with default values.    
    CircularBuffer() : start(0), end(0), count(0), buf_capacity(0) {}

    // Destructor: Cleans up the CircularBuffer object.
    ~CircularBuffer() {}

    // Copy Constructor: Creates a copy of an existing CircularBuffer object.
    CircularBuffer(const CircularBuffer &cb)
        : buffer(cb.buffer), start(cb.start), end(cb.end), count(cb.count), buf_capacity(cb.buf_capacity) {}

    // Constructor with Capacity: Initializes a CircularBuffer with a specified capacity.
    explicit CircularBuffer(int capacity)
        : buffer(capacity), start(0), end(0), count(0), buf_capacity(capacity) {}

    // Constructor with Capacity and Fill Element: Initializes a CircularBuffer 
    // with a specified capacity and fills it with a specified element.
    CircularBuffer(int capacity, const value_type &elem)
        : buffer(capacity, elem), start(0), end(0), count(capacity), buf_capacity(capacity) {}

    // Indexing Operators: Provides access to elements by index without bounds checking.
    value_type &operator[](int i) {
        return buffer[(start + i) % buf_capacity];
    }

    const value_type &operator[](int i) const {
        return buffer[(start + i) % buf_capacity];
    }

    // Access Methods with Bounds Checking: Provides access to elements by index with bounds checking.
    value_type &at(int i) {
        if (i < 0 || i >= count) throw std::out_of_range("Index out of range");
        return buffer[(start + i) % buf_capacity];
    }

    const value_type &at(int i) const {
        if (i < 0 || i >= count) throw std::out_of_range("Index out of range");
        return buffer[(start + i) % buf_capacity];
    }

    // Methods to access the first and last elements of the buffer.
    value_type &front() { return buffer[start]; }
    
    value_type &back() { return buffer[(end - 1 + buf_capacity) % buf_capacity]; }
    
    const value_type &front() const { return buffer[start]; }

    const value_type &back() const { return buffer[(end - 1 + buf_capacity) % buf_capacity]; }

    // Method to linearize the buffer, making it contiguous.
    value_type *linearize() {
        if (start <= end) {
            return &buffer[start];
        } else {
            std::rotate(buffer.begin(), buffer.begin() + start, buffer.end());
            start = 0;
            end = count;
            return &buffer[0];
        }
    }

    // Method to check if the buffer is linearized.
    bool is_linearized() const { return start == 0; }

    // Method to rotate the buffer so that the element at new_begin becomes the first element.
    void rotate(int new_begin) {
        std::rotate(buffer.begin(), buffer.begin() + new_begin, buffer.end());
        start = new_begin;
        end = (start + count) % buf_capacity;
    }

    // Method to get the size of the buffer (number of elements currently stored).
    int size() const { return count; }

    // Method to check if the buffer is empty.
    bool empty() const { return count == 0; }

    // Method to check if the buffer is full.
    bool full() const { return count == buf_capacity; }

    // Method to get the number of free slots in the buffer.
    int reserve() const { return buf_capacity - count; }

    // Method to get the capacity of the buffer (maximum number of elements it can hold).
    int capacity() const { return buf_capacity; }

    // Method to set a new capacity for the buffer.
    void set_capacity(int new_capacity) {
        if (new_capacity < count) throw std::invalid_argument("New capacity cannot be less than current size");
        buffer.resize(new_capacity);
        buf_capacity = new_capacity;
    }

    // Method to resize the buffer, adding new elements if necessary.
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

    // Assignment operator: Assigns the values from another CircularBuffer to this one.
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

    // Method to swap the contents of this buffer with another buffer.
    void swap(CircularBuffer &cb) {
        std::swap(buffer, cb.buffer);
        std::swap(start, cb.start);
        std::swap(end, cb.end);
        std::swap(count, cb.count);
        std::swap(buf_capacity, cb.buf_capacity);
    }

    // Method to add an element to the end of the buffer.
    void push_back(const value_type &item = value_type()) {
        if (full()) {
            start = (start + 1) % buf_capacity; // Increment start if buffer is full
        }
        buffer[end] = item;
        end = (end + 1) % buf_capacity;
        count = std::min(count + 1, buf_capacity);
    }

    // Method to add an element to the front of the buffer.
    void push_front(const value_type &item = value_type()) {
        if (full()) {
            end = (end - 1 + buf_capacity) % buf_capacity; // Decrement end if buffer is full
        }
        start = (start - 1 + buf_capacity) % buf_capacity;
        buffer[start] = item;
        count = std::min(count + 1, buf_capacity);
    }

    // Method to remove the last element from the buffer.
    void pop_back() {
        if (empty()) throw std::underflow_error("Buffer is empty");
        end = (end - 1 + buf_capacity) % buf_capacity;
        --count;
    }

    // Method to remove the first element from the buffer.
    void pop_front() {
        if (empty()) throw std::underflow_error("Buffer is empty");
        start = (start + 1) % buf_capacity;
        --count;
    }

    // Method to insert an element at a specific position in the buffer.
    void insert(int pos, const value_type &item = value_type()) {
        if (pos < 0 || pos >= count) throw std::out_of_range("Index out of range");
        push_back();
        for (int i = count - 1; i > pos; --i) {
            buffer[(start + i) % buf_capacity] = buffer[(start + i - 1) % buf_capacity];
        }
        buffer[(start + pos) % buf_capacity] = item;    
    }

    // Method to erase a range of elements from the buffer.
    void erase(int first, int last) {
        if (first < 0 || last > count || first >= last) throw std::out_of_range("Invalid range");
        for (int i = 0; i < count - last; ++i) {
            buffer[(start + first + i) % buf_capacity] = buffer[(start + last + i) % buf_capacity];
        }
        count -= (last - first);
        end = (start + count) % buf_capacity;
    }

    // Method to clear the buffer.
    void clear() {
        start = 0;
        end = 0;
        count = 0;
    }
};

// Equality operator: Checks if two CircularBuffers are equal.
bool operator==(const CircularBuffer &a, const CircularBuffer &b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// Inequality operator: Checks if two CircularBuffers are not equal.
bool operator!=(const CircularBuffer &a, const CircularBuffer &b) {
    return !(a == b);
}