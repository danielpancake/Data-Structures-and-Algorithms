#ifndef _ICIRCULAR_BOUNDED_QUEUE_H_
#define _ICIRCULAR_BOUNDED_QUEUE_H_

#include "BasicContainer.h"
#include <cstddef>

template <class T, const std::size_t C>
class ICircularBoundedQueue : public BasicContainer<T, C> {
    public:
        virtual void offer(T) = 0;

        virtual T poll() = 0;
        virtual T peek() = 0;
};
#endif
