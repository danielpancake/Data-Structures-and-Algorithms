#ifndef _ISET_H_
#define _ISET_H_

#include <cstddef>

template <class T>
class ISet {
    protected:
        std::size_t setSize = 0;

    public:
        virtual void add(T) = 0;
        virtual void remove(T) = 0;

        virtual bool contains(T) = 0;

        virtual std::size_t size() { return setSize; };
        virtual bool isEmpty() { return setSize == 0; };
};
#endif
