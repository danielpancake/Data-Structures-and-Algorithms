#ifndef _QUEUED_BOUNDED_STACK_H_
#define _QUEUED_BOUNDED_STACK_H_

#include "ArrayCircularBoundedQueue.h"
#include "IBoundedStack.h"

/* TODO: Explain approach to the implementation of QueuedBoundedStack.
 * Write down the explanation as a paragraph in the comments to the class QueuedBoundedStack
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
            while (!q_p->isEmpty()) {
                q_s->offer(q_p->poll());
            }

            q_p->offer(value);

            int s = q_s->size() - q_s->isFull();
            for (int i = 0; i < s; ++i) {
                q_p->offer(q_s->poll());
            }
            
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
