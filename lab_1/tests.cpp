#include "gtest/gtest.h"
#include "ring_buffer.hpp"

TEST(CircularBufferTests, Initialization) {
    CircularBuffer buffer(5);
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 5);
    EXPECT_TRUE(buffer.empty());
    EXPECT_FALSE(buffer.full());
}

TEST(CircularBufferTests, PushBack) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');
    
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer[2], 'c');
    EXPECT_FALSE(buffer.empty());
    EXPECT_FALSE(buffer.full());
}

TEST(CircularBufferTests, PushFront) {
    CircularBuffer buffer(5);
    buffer.push_front('a');
    buffer.push_front('b');
    buffer.push_front('c');

    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer[0], 'c');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer[2], 'a');
    EXPECT_FALSE(buffer.empty());
    EXPECT_FALSE(buffer.full());
}

TEST(CircularBufferTests, PopBack) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    buffer.pop_back();

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_FALSE(buffer.empty());
}

TEST(CircularBufferTests, PopFront) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    buffer.pop_front();

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 'b');
    EXPECT_EQ(buffer[1], 'c');
    EXPECT_FALSE(buffer.empty());
}

TEST(CircularBufferTests, Clear) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    buffer.clear();

    EXPECT_EQ(buffer.size(), 0);
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.capacity(), 5);
}

TEST(CircularBufferTests, FrontAndBack) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    EXPECT_EQ(buffer.front(), 'a');
    EXPECT_EQ(buffer.back(), 'c');

    buffer.pop_front();

    EXPECT_EQ(buffer.front(), 'b');
    EXPECT_EQ(buffer.back(), 'c');
}

TEST(CircularBufferTests, Insert) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('d');

    buffer.insert(2, 'c');

    EXPECT_EQ(buffer.size(), 4);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer[2], 'c');
    EXPECT_EQ(buffer[3], 'd');
}

TEST(CircularBufferTests, Erase) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');
    buffer.push_back('d');

    buffer.erase(1, 3);

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'd');
}

TEST(CircularBufferTests, Resize) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    buffer.resize(5, 'x');

    EXPECT_EQ(buffer.size(), 5);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer[2], 'c');
    EXPECT_EQ(buffer[3], 'x');
    EXPECT_EQ(buffer[4], 'x');
}

TEST(CircularBufferTests, SetCapacity) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    buffer.set_capacity(10);

    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.capacity(), 10);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer[2], 'c');
}

TEST(CircularBufferTests, Swap) {
    CircularBuffer buffer1(5);
    buffer1.push_back('a');
    buffer1.push_back('b');

    CircularBuffer buffer2(5);
    buffer2.push_back('x');
    buffer2.push_back('y');
    buffer2.push_back('z');

    buffer1.swap(buffer2);

    EXPECT_EQ(buffer1.size(), 3);
    EXPECT_EQ(buffer1[0], 'x');
    EXPECT_EQ(buffer1[1], 'y');
    EXPECT_EQ(buffer1[2], 'z');

    EXPECT_EQ(buffer2.size(), 2);
    EXPECT_EQ(buffer2[0], 'a');
    EXPECT_EQ(buffer2[1], 'b');
}

TEST(CircularBufferTests, At) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');

    EXPECT_EQ(buffer.at(0), 'a');
    EXPECT_EQ(buffer.at(1), 'b');
    EXPECT_EQ(buffer.at(2), 'c');

    EXPECT_THROW(buffer.at(3), std::out_of_range);
}

TEST(CircularBufferTests, Linearize) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');
    buffer.push_back('d');
    buffer.push_back('e');
    
    buffer.pop_front();
    buffer.push_back('f');

    EXPECT_FALSE(buffer.is_linearized());
    buffer.linearize();
    EXPECT_TRUE(buffer.is_linearized());

    EXPECT_EQ(buffer[0], 'b');
    EXPECT_EQ(buffer[1], 'c');
    EXPECT_EQ(buffer[2], 'd');
    EXPECT_EQ(buffer[3], 'e');
    EXPECT_EQ(buffer[4], 'f');
}

TEST(CircularBufferTests, AssignmentOperator) {
    CircularBuffer buffer1(5);
    buffer1.push_back('a');
    buffer1.push_back('b');
    buffer1.push_back('c');

    CircularBuffer buffer2 = buffer1;

    EXPECT_EQ(buffer2.size(), 3);
    EXPECT_EQ(buffer2[0], 'a');
    EXPECT_EQ(buffer2[1], 'b');
    EXPECT_EQ(buffer2[2], 'c');
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
