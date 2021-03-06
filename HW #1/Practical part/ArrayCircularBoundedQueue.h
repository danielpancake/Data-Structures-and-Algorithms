#ifndef _ARRAY_CIRCULAR_BOUNDED_QUEUE_H_
#define _ARRAY_CIRCULAR_BOUNDED_QUEUE_H_

#ifdef DEBUG
#include <iostream>
#endif

#include "ICircularBoundedQueue.h"

/**
 * @brief Implementation of Circular Bounded Queue with Arrays.
 * All methods have time complexity of O(1)
 */
template <class T>
class ArrayCircularBoundedQueue : public ICircularBoundedQueue<T> {
    private:
        T *array;
        int rear = -1;

        int getFront() {
            int f = rear - this->size() + 1;
            return this->capacity() * (f < 0) + f;
        };

    public:
        ArrayCircularBoundedQueue() : ICircularBoundedQueue<T>::ICircularBoundedQueue(0){};
        // Inheriting constructor of the super class to inherit the constructor of BoundedContainer class
        ArrayCircularBoundedQueue(size_t capacity) : ICircularBoundedQueue<T>::ICircularBoundedQueue(capacity) {
            array = new T[this->capacity()];
        };

        ArrayCircularBoundedQueue(const ArrayCircularBoundedQueue<T> &arcq) : ArrayCircularBoundedQueue(arcq.containerCapacity) {
            this->containerSize = arcq.containerSize;
            rear = arcq.rear;
            
            for (int i = 0; i < this->containerSize; ++i) {
                array[i] = arcq.array[i];
            };
        };

        ~ArrayCircularBoundedQueue() {
            delete[] array;
        };

        virtual void offer(T value) {
            rear = (rear + 1) % this->capacity();
            array[rear] = value;

            if (!this->isFull()) {
                ++(this->containerSize);
            }
        };

        virtual T poll() {
            if (this->isEmpty()) {
                rear = -1; // Resetting rear pointer and returninig an object of the T type
                return {}; // initialized with an empty list-initializer
            }
            
            T value = array[getFront()];
            --(this->containerSize);
            return value;
        };

        virtual T peek() {
            return array[getFront()];
        };

        virtual void flush() {
            this->containerSize = 0;
            rear = -1;
        };

        #ifdef DEBUG
        void __debugPrint() {
            int f = getFront();
            for (int i = 0; i < this->size(); ++i) {
                std::cout << array[(f + i) % this->capacity()] << " ";
            };
            std::cout << std::endl;
        };
        #endif
};
#endif
