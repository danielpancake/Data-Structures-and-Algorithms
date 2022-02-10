#ifndef _ARRAY_CIRCULAR_BOUNDED_QUEUE_H_
#define _ARRAY_CIRCULAR_BOUNDED_QUEUE_H_

#ifdef DEBUG
#include <iostream>
#endif

#include "ICircularBoundedQueue.h"
#include <cstddef>

template <class T, const std::size_t C>
class ArrayCircularBoundedQueue : public ICircularBoundedQueue<T, C> {
    private:
        T *array;
        int rear = -1;

        int getFront() {
            int f = rear - this->size() + 1;
            return C * (f < 0) + f;
        };

    public:
        ArrayCircularBoundedQueue() {
            array = new T[C];
        };

        virtual void offer(T value) {
            rear = (rear + 1) % C;
            array[rear] = value;

            if (!this->isFull()) {
                ++(this->containerSize);
            }
        };

        virtual T poll() {
            if (this->isEmpty()) {
                rear = -1;
                return {};
            } else {
                --(this->containerSize);
            }

            return array[getFront()];
        };

        virtual T peek() {
            return array[getFront()];
        };

        virtual void flush() {
            this->containerSize = 0;
            rear = -1;
        };

        #ifdef DEBUG
        void __debug_print() {
            int f = getFront();
            for (int i = 0; i < this->size(); ++i) {
                std::cout << array[(f + i) % C] << " ";
            };
            std::cout << std::endl;
        };
        #endif
};
#endif
