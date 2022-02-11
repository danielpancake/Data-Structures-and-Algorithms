#ifndef _ICIRCULAR_BOUNDED_QUEUE_H_
#define _ICIRCULAR_BOUNDED_QUEUE_H_

#include "BoundedContainer.h"

template <class T>
class ICircularBoundedQueue : public BoundedContainer<T> {
    public:
        using BoundedContainer<T>::BoundedContainer;

        virtual void offer(T) = 0;

        virtual T poll() = 0;
        virtual T peek() = 0;
};
#endif
