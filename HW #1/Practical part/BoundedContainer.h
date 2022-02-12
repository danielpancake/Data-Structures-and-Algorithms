#ifndef _BOUNDED_CONTAINER_H_
#define _BOUNDED_CONTAINER_H_

#include <cstddef>

class BoundedContainer {
    protected:
        std::size_t containerCapacity = 0;
        std::size_t containerSize = 0;

    public:
        BoundedContainer(std::size_t capacity) {
            containerCapacity = capacity;
        };

        std::size_t capacity() { return containerCapacity; };
        std::size_t size() { return containerSize; };

        bool isEmpty() { return containerSize == 0; };
        bool isFull() { return containerSize == containerCapacity; };
};
#endif
