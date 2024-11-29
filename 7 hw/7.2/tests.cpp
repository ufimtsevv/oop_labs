#include <gtest/gtest.h>
#include "time.h"

// тест конструктора 
TEST(TimeTest, Constructor) {
    Time t1(1, 2, 3);
    EXPECT_EQ(t1.hours, 1);
    EXPECT_EQ(t1.minutes, 2);
    EXPECT_EQ(t1.seconds, 3);
    
    Time t2(25, 61, 61);
    EXPECT_EQ(t2.hours, 2);
    EXPECT_EQ(t2.minutes, 2);
    EXPECT_EQ(t2.seconds, 1);

    // провальный тест
    Time t3(0, 0, 0);
    EXPECT_EQ(t3.hours, 1);  // должно быть 0
}

// тест метода Normalize
TEST(TimeTest, Normalize) {
    Time t1(1, 70, 80);
    EXPECT_EQ(t1.hours, 2);
    EXPECT_EQ(t1.minutes, 11);
    EXPECT_EQ(t1.seconds, 20);

    // провальный тест
    Time t2(0, 0, 0);
    t2.Normalize();
    EXPECT_EQ(t2.minutes, 1);  // должно быть 0
}

// тест метода ToSeconds
TEST(TimeTest, ToSeconds) {
    Time t1(1, 1, 1);
    EXPECT_EQ(t1.ToSeconds(), 3661);

    Time t2(0, 0, 59);
    EXPECT_EQ(t2.ToSeconds(), 59);

    // провальный тест
    Time t3(0, 1, 0);
    EXPECT_EQ(t3.ToSeconds(), 100);  // должно быть 60
}

// тест оператора -
TEST(TimeTest, SubtractionOperator) {
    Time t1(2, 30, 0);
    Time t2(1, 15, 0);
    Time result = t1 - t2;
    EXPECT_EQ(result.hours, 1);
    EXPECT_EQ(result.minutes, 15);
    EXPECT_EQ(result.seconds, 0);

    // провальный тест
    Time t3(0, 0, 0);
    Time t4(0, 0, 0);
    result = t3 - t4;
    EXPECT_EQ(result.hours, 1);  // должно быть 0
}

// тест оператора -=
TEST(TimeTest, SubtractionAssignmentOperator) {
    Time t1(2, 30, 0);
    Time t2(1, 15, 0);
    t1 -= t2;
    EXPECT_EQ(t1.hours, 1);
    EXPECT_EQ(t1.minutes, 15);
    EXPECT_EQ(t1.seconds, 0);

    // провальный тест
    Time t3(0, 0, 0);
    t3 -= t1;
    EXPECT_EQ(t3.hours, 1);  // должно быть -1
}

// тест оператора ==
TEST(TimeTest, EqualityOperator) {
    Time t1(1, 1, 1);
    Time t2(1, 1, 1);
    EXPECT_TRUE(t1 == t2);

    Time t3(2, 2, 2);
    EXPECT_FALSE(t1 == t3);

    // провальный тест
    EXPECT_TRUE(t1 == t3);  // должно быть false
}

// тест метода GetCount
TEST(TimeTest, GetCount) {
    EXPECT_EQ(Time::GetCount(), 0);

    Time t1(1, 1, 1);
    EXPECT_EQ(Time::GetCount(), 1);

    {
        Time t2(2, 2, 2);
        EXPECT_EQ(Time::GetCount(), 2);
    }

    EXPECT_EQ(Time::GetCount(), 1);  // объект t2 разрушен

    // провальный тест
    EXPECT_EQ(Time::GetCount(), 2);  // должно быть 1
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}