#ifndef _IBOUNDED_STACK_H_
#define _IBOUNDED_STACK_H_

#include "BoundedContainer.h"

/**
 * @brief Abstract class for Bounded Stack. Inherites all methods from Bounded Container class
 */
template <class T>
class IBoundedStack : public BoundedContainer {
    public:
        using BoundedContainer::BoundedContainer;
        
        /**
         * @brief Pushes an element onto the stack and removes the oldest element if stack is full */
        virtual void push(T) = 0;

        /**
         * @brief Removes all elements from the stack */
        virtual void flush() = 0;

        /**
         * @brief Removes an element from the top of the stack
         * @return T Removed element */
        virtual T pop() = 0;

        /**
         * @brief Looks at the element at the top of the stack without removing it
         * @return T Element at the top of the stack */
        virtual T top() = 0;
};
#endif
