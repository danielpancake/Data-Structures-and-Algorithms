#ifndef _QUEUED_BOUNDED_STACK_H_
#define _QUEUED_BOUNDED_STACK_H_

#include "ArrayCircularBoundedQueue.h"
#include "IBoundedStack.h"
#include <cstddef>

/* TODO: Explain approach to the implementation of QueuedBoundedStack.
 * Write down the explanation as a paragraph in the comments to the class QueuedBoundedStack
 */
template <class T, const std::size_t C>
class QueuedBoundedStack : public IBoundedStack<T, C> {
    private:
        // Declaring and initializing primary and secondary queues
        ArrayCircularBoundedQueue<T, C> *q_p, *q_s;

    public:
        QueuedBoundedStack() {
            q_p = new ArrayCircularBoundedQueue<T, C>;
            q_s = new ArrayCircularBoundedQueue<T, C>;
        };

        virtual void flush() {
            q_p->flush();
            q_s->flush();
        }

        virtual void push(T value) {
            for (int i = 0; i < this->size(); ++i) {
                q_s->offer(q_p->poll());
            }

            q_p->offer(value);

            for (int i = 0; i < this->size(); ++i) {
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

        #ifdef DEBUG
        void __debug_print() { q_p->__debug_print(); };
        #endif
};
#endif
