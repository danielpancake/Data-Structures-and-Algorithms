#define DEBUG
#include "ArrayCircularBoundedQueue.h"

int main() {
    ArrayCircularBoundedQueue<int, 3> a;
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
    
    return 0;
}
