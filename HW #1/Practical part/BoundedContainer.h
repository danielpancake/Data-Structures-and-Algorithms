#ifndef _BOUNDED_CONTAINER_H_
#define _BOUNDED_CONTAINER_H_

#include <cstddef>

/**
 * @brief Abstract class for some Bounded Container (e.g.: Circular Bounded Queue or Bounded Stack)*/
class BoundedContainer {
    protected:
        std::size_t containerCapacity = 0;
        std::size_t containerSize = 0;

    public:
        BoundedContainer(std::size_t capacity) {
            containerCapacity = capacity;
        };

        /**
         * @brief Returns capacity (maximum size) of the bounded container
         * @return std::size_t capacity (maximum size) */
        std::size_t capacity() { return containerCapacity; };

        /**
         * @brief Returns size (number of elements) of the bounded container
         * @return std::size_t size (number of elements) */
        std::size_t size() { return containerSize; };

        /**
         * @brief Determine whether bounded container is empty
         * @return TRUE if bounded container is empty and FALSE otherwise */
        bool isEmpty() { return containerSize == 0; };

        /**
         * @brief Determine whether bounded container is full
         * @return TRUE if bounded container is full and FALSE otherwise */
        bool isFull() { return containerSize == containerCapacity; };
};
#endif
