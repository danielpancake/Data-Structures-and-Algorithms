#ifndef _QUEUED_BOUNDED_STACK_H_
#define _QUEUED_BOUNDED_STACK_H_

#include "ArrayCircularBoundedQueue.h"
#include "IBoundedStack.h"

/**
 * @brief Implementation of Queued Bounded Stack with two Bounded Queues.
 * In this implementation method PUSH has time complexity of O(n),
 * all other methods (pop, top, and flush) have time complexity of O(1)
 */
template <class T>
class QueuedBoundedStack : public IBoundedStack<T> {
    private:
        // Declaring and initializing primary and secondary queues
        ArrayCircularBoundedQueue<T> *q_p, *q_s;

    public:
        QueuedBoundedStack() : IBoundedStack<T>::IBoundedStack(1) {};
        QueuedBoundedStack(std::size_t capacity) : IBoundedStack<T>::IBoundedStack(capacity) {
            q_p = new ArrayCircularBoundedQueue<T>(capacity);
            q_s = new ArrayCircularBoundedQueue<T>(capacity);
        };

        QueuedBoundedStack(const QueuedBoundedStack<T> &qs) : IBoundedStack<T>::IBoundedStack(qs.containerCapacity) {
            q_p = new ArrayCircularBoundedQueue<T>(*qs.q_p);
            q_s = new ArrayCircularBoundedQueue<T>(*qs.q_s);
        };

        ~QueuedBoundedStack() {
            delete q_p;
            delete q_s;
        };

        virtual void push(T value) {
            /* Implementation note:
             * First, we move everything from the primary queue (q_p) to the secondary queue (q_s).
             * Then, a new value is added in front of the q_p. Finally, we move every element
             * from the q_s back to the q_p. If q_s happens to be full, we move every element but last
             * and delete it */
            while (!q_p->isEmpty()) {
                q_s->offer(q_p->poll());
            }
            
            q_p->offer(value);

            while (!q_s->isEmpty() && !q_p->isFull()) {
                q_p->offer(q_s->poll());
            }

            while (!q_s->isEmpty()) { q_s->poll(); }

            this->containerSize = q_p->size();
        };
        
        virtual T pop() {
            T value = q_p->poll();
            this->containerSize = q_p->size();
            return value;
        };
        
        virtual T top() {
            T value = q_p->peek();
            return value;
        };

        virtual void flush() {
            q_p->flush();
            q_s->flush();

            this->containerSize = 0;
        };

        #ifdef DEBUG
        void __debugPrint() { q_p->__debugPrint(); };
        #endif
};
#endif
