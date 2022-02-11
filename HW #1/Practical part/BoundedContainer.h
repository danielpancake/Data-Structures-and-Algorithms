#ifndef _BOUNDED_CONTAINER_H_
#define _BOUNDED_CONTAINER_H_

#include <cstddef>

template <class T>
class BoundedContainer {
    protected:
        std::size_t containerCapacity = 0;
        std::size_t containerSize = 0;

    public:
        explicit BoundedContainer(std::size_t capacity) {
            containerCapacity = capacity;
        };

        virtual void flush() = 0;

        virtual std::size_t capacity() { return containerCapacity; };
        virtual std::size_t size() { return containerSize; };

        virtual bool isEmpty() { return containerSize == 0; };
        virtual bool isFull() { return containerSize == containerCapacity; };
};
#endif
