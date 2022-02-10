#ifndef _BASIC_CONTAINER_H_
#define _BASIC_CONTAINER_H_

#include <cstddef>

template <class T, const std::size_t C>
class BasicContainer {
    protected:
        std::size_t containerSize = 0;

    public:
        virtual void flush() = 0;

        virtual std::size_t capacity() { return C; };
        virtual std::size_t size() { return containerSize; };

        virtual bool isEmpty() { return containerSize == 0; };
        virtual bool isFull() { return containerSize == C; };
};
#endif
