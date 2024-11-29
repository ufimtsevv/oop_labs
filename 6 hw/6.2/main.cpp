#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include "time.hpp"

int main() {
    try {
        Time* dynamicTime = new Time(2, 30, 45);
        Time* dynamicArray = new Time[3]{
            Time(1, 10, 20),
            Time(2, 20, 30),
            Time(3, 30, 40)
        };

        std::cout << "Dynamic Time: ";
        dynamicTime->Print();
        for (int i = 0; i < 3; ++i) {
            std::cout << "Dynamic Array Time " << i + 1 << ": ";
            dynamicArray[i].Print();
        }

        delete dynamicTime;
        delete[] dynamicArray;

        std::vector<std::shared_ptr<Time>> timeVector = {
            std::make_shared<Time>(1, 1, 1),
            std::make_shared<Time>(2, 2, 2),
            std::make_shared<Time>(3, 3, 3)
        };
        std::list<std::shared_ptr<Time>> timeList = {
            std::make_shared<Time>(4, 4, 4),
            std::make_shared<Time>(5, 5, 5),
            std::make_shared<Time>(6, 6, 6)
        };

        std::cout << "Vector of Times: " << std::endl;
        for (const auto& t : timeVector) {
            t->Print();
        }

        std::cout << "List of Times: " << std::endl;
        for (const auto& t : timeList) {
            t->Print();
        }

        std::shared_ptr<Time> sharedTime = std::make_shared<Time>(7, 7, 7);
        std::unique_ptr<Time> uniqueTime = std::make_unique<Time>(8, 8, 8);

        std::cout << "Shared Pointer Time: ";
        sharedTime->Print();
        std::cout << "Unique Pointer Time: ";
        uniqueTime->Print();

        // исключение
        Time t5(-1, 0, 0);
        
        std::cout << "Final Time object count: " << Time::GetCount() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
