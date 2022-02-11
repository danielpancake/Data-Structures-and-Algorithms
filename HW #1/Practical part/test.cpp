#define DEBUG

#include "ArrayCircularBoundedQueue.h"
#include "QueuedBoundedStack.h"

int main() {
    ArrayCircularBoundedQueue<int> a(3);
    a.offer(1);
    a.offer(2);
    a.offer(3);
    a.__debug_print();

    a.poll();
    a.poll();
    a.__debug_print();

    a.offer(4);
    a.offer(5);
    a.__debug_print();

    QueuedBoundedStack<int> b(10);
    b.push(13);
    b.push(14);
    b.push(15);
    b.__debug_print();
    
    b.pop();
    b.__debug_print();

    return 0;
}
