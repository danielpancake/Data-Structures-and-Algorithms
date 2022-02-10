#ifdef DEBUG
#include <iostream>
#endif

template <class T, const std::size_t C>
class ICircularBoundedQueue {
    protected:
        int queueSize = 0;

    public:
        virtual void offer(T) = 0;

        virtual T poll() = 0;
        virtual T peek() = 0;

        virtual void flush() = 0;

        virtual int capacity() { return C; };
        virtual int size() { return queueSize; };

        virtual bool isEmpty() { return queueSize == 0; };
        virtual bool isFull() { return queueSize == C; };
};

template <class T, const std::size_t C>
class ArrayCircularBoundedQueue : public ICircularBoundedQueue<T, C> {
    private:
        T *array;
        int rear = -1;

        int getFront() {
            int f = rear - this->queueSize + 1;
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
                ++(this->queueSize);
            }
        };

        virtual T poll() {
            if (this->isEmpty()) {
                rear = -1;
                return 0;
            } else {
                --(this->queueSize);
            }

            return array[getFront()];
        };

        virtual T peek() {
            return array[getFront()];
        };

        virtual void flush() {
            this->queueSize = 0;
            rear = -1;
        };

        #ifdef DEBUG
        void __debug_print() {
            int f = getFront();
            for (int i = 0; i < this->queueSize; ++i) {
                std::cout << array[(f + i) % C] << " ";
            };
            std::cout << std::endl;
        };
        #endif
};
