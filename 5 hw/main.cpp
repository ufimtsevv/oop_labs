#include <iostream>
#include "time.hpp"

int main() {
    Time t1(10, 20, 30);
    Time t2(5, 45, 15);

    std::cout << "Time 1: ";
    t1.Print();
    std::cout << "Time 2: ";
    t2.Print();
    
    std::cout << "Time 1 in seconds: " << t1.ToSeconds() << std::endl;
    std::cout << "Time 2 in seconds: " << t2.ToSeconds() << std::endl;
    
    Time t3 = t1 - t2;
    std::cout << "Difference (t1 - t2): ";
    t3.Print();
    
    t1 -= t2;
    std::cout << "After t1 -= t2, t1: ";
    t1.Print();
    
    Time t4(4, 35, 15);
    std::cout << "Time 4: ";
    t4.Print();
    std::cout << "t2 == t4: " << (t2 == t4) << std::endl;

    std::cout << "Current Time object count: " << Time::GetCount() << std::endl;

    return 0;
}
