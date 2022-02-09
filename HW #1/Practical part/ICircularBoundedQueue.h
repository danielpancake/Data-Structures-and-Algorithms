#ifdef DEBUG
#include <iostream>
#endif

template <class T, int C>
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

template <class T, int C>
class ArrayCircularBoundedQueue : public ICircularBoundedQueue<T, C> {
    private:
        T *array;
        int front = 0, rear = -1;

    public:
        ArrayCircularBoundedQueue() {
            array = new T[C];
        };

        virtual void offer(T value) {
            rear = (rear + 1) % C;
            array[rear] = value;

            if (this->isFull()) {
                front = (rear + 1) % C;
            } else {
                ++(this->queueSize);
            }
        };

        virtual T poll() {
            int t = front;
            front = (front + 1) % C;
            
            if (this->isEmpty()) {
                front = 0;
                rear = -1;

                return NULL;
            } else {
                --(this->queueSize);
            }

            return array[t];
        };

        virtual T peek() {
            return array[front];
        };

        virtual void flush() {
            front = 0;
            rear = -1;

            this->queueSize = 0;
        };

        #ifdef DEBUG
        void __debug_print() {
            for (int i = 0; i < C; ++i) {
                std::cout << array[i] << " ";
            };
            std::cout << std::endl;
        };
        #endif
};
