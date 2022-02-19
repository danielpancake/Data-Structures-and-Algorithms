#ifndef _ISET_H_
#define _ISET_H_

#include <cstddef>

/**
 * @brief Abstract class for Set
 */
template <class T>
class ISet {
    protected:
        std::size_t setSize = 0;

    public:
        /**
         * @brief Adds an element to the set */
        virtual void add(T) = 0;

        /**
         * @brief Removes an element from the set */
        virtual void remove(T) = 0;

        /**
         * @brief Checks if an item belongs to the set
         * @return TRUE if an item belongs to the set and FALSE otherwise */
        virtual bool contains(T) = 0;

        /**
         * @brief Returns size (number of elements) of the bounded container
         * @return std::size_t size (number of elements) */
        virtual std::size_t size() { return setSize; };

        /**
         * @brief Determine whether set is empty
         * @return TRUE if set is empty and FALSE otherwise */
        virtual bool isEmpty() { return setSize == 0; };
};
#endif
