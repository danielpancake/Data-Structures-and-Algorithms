#ifndef _ICIRCULAR_BOUNDED_QUEUE_H_
#define _ICIRCULAR_BOUNDED_QUEUE_H_

#include "BoundedContainer.h"

/**
 * @brief Abstract class for Circular Bounded Queue. Inherites all methods from Bounded Container class */
template <class T>
class ICircularBoundedQueue : public BoundedContainer {
    public:
        // Using inherited constructor
        using BoundedContainer::BoundedContainer;

        /**
         * @brief Inserts an element to the rear of the queue,
         * overwrites the oldest elements when the queue is full */
        virtual void offer(T) = 0;

        /**
         * @brief Removes all elements from the queue */
        virtual void flush() = 0;

        /**
         * @brief Removes an element from the front of the queue
         * @return T Removed element */
        virtual T poll() = 0;
        
        /**
         * @brief Looks at the element at the front of the queue without removing it
         * @return T Element at the front of the queue */
        virtual T peek() = 0;
};
#endif
