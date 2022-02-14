#define DEBUG

#include <iostream>
#include <string>

#include "ArrayCircularBoundedQueue.h"
#include "DoubleHashSet.h"
#include "QueuedBoundedStack.h"

int main() {
    ArrayCircularBoundedQueue<std::string> c(20);
    c.offer("I'm first");
    ArrayCircularBoundedQueue<std::string> d(c);
    std::cout << c.poll() << " and " << d.poll() << "\n\n";

    DoubleHashSet<std::string> a;
    a.add("aaa");

    DoubleHashSet<std::string> b = a;
    std::cout << a.contains("aaa") << " " << b.contains("aaa") << "\n\n";

    QueuedBoundedStack<std::string> e(20);
    e.push("Hi!");
    QueuedBoundedStack<std::string> f(e);
    std::cout << e.pop() << " " << f.pop() << "\n";

    return 0;
}
