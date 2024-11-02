#include <iostream>
#include "time.h"
using namespace std;

int main() {
    Time t(0, 2, 120);
    t.Print();
    cout << t.ToSeconds() << endl;

    Time t1(10, 45, 30);
    Time t2(2, 15, 50);

    Time t3 = t1 - t2;
    t3.Print();

    t1 -= t2;
    t1.Print();

    cout << (t1 == t3) << endl;

    return 0;
}