#define DEBUG

#include <iostream>
#include <string>

#include "ArrayCircularBoundedQueue.h"
#include "DoubleHashSet.h"
#include "QueuedBoundedStack.h"

int main() {
    ArrayCircularBoundedQueue<std::string> c(1);
    c.offer("I'm first");
    ArrayCircularBoundedQueue<std::string> d(c);
    std::cout << c.poll() << " and " << d.poll() << "\n\n";

    DoubleHashSet<std::string> a;
    a.add("aaa");

    DoubleHashSet<std::string> b = a;
    std::cout << a.contains("aaa") << " " << b.contains("aaa") << "\n\n";

    QueuedBoundedStack<std::string> e(1);
    e.push("Hi!");
    QueuedBoundedStack<std::string> f(e);
    std::cout << e.pop() << " " << f.pop() << "\n";

    QueuedBoundedStack<std::string> g(3);
    g.push("1");
    g.push("2");
    g.push("3");
    g.push("4");
    g.push("5");
    g.push("6");

    for (int i = 0; i < 3; i++) {
        std::cout << g.pop() << " ";
    }

    return 0;
}
