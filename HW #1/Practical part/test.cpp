#define DEBUG

#include <iostream>
#include "DoubleHashSet.h"

int main() {
    DoubleHashSet<int> a;
    a.add(12);
    a.add(13);
    a.add(14);
    a.add(15);
    a.add(16);
    a.add(17);
    a.add(18);
    a.add(19);
    a.add(20);
    a.add(21);
    a.add(22);
    a.add(23);
    a.add(24);
    a.add(25);

    a.remove(12);

    int in; std::cin >> in;
    std::cout << a.contains(in) << std::endl;

    return 0;
}
