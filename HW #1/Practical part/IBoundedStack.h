#ifndef _IBOUNDED_STACK_H_
#define _IBOUNDED_STACK_H_

#include <cstddef>

template <class T, const std::size_t C>
class IBoundedStack : public BasicContainer <T, C>{
    public:
        virtual void push(T) = 0;

        virtual T pop() = 0;
        virtual T top() = 0;
};
#endif
