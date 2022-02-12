#ifndef _IBOUNDED_STACK_H_
#define _IBOUNDED_STACK_H_

#include "BoundedContainer.h"

template <class T>
class IBoundedStack : public BoundedContainer {
    public:
        using BoundedContainer::BoundedContainer;
        
        virtual void push(T) = 0;
        virtual void flush() = 0;

        virtual T pop() = 0;
        virtual T top() = 0;
};
#endif
