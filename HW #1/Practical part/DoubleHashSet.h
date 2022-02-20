#ifndef _DOUBLE_HASH_SET_H_
#define _DOUBLE_HASH_SET_H_

#include "ISet.h"
#include <cstring>
#include <functional>

#define MAGIC_NUMBER 5231 // Used for intermediate hash function compression 

/**
 * @brief User-defined Pair structure
 * @tparam F Type of the first element 
 * @tparam S TYpe of the second element
 */
template<class F, class S>
class Pair {
    public:
        F first; S second;

        Pair() {};
        Pair(const F &f, const S &s) : first(f), second(s) {};

        bool operator==(Pair const &p) {
            return p.first == this->first && p.second == this->second;
        };
};

/**
 * @brief Wrapper class for entries in HashTable
 */
template<class V>
class HashEntry {
    private:
        bool hashEntryIsDead = false;
        bool hashEntryIsEmpty = true;

        V value;

    public:
        HashEntry() {
            value = {};
        };

        HashEntry(V v) {
            hashEntryIsEmpty = false;
            value = v;
        };

        HashEntry(const HashEntry &e) {
            hashEntryIsDead = e.hashEntryIsDead;
            hashEntryIsEmpty = e.hashEntryIsEmpty;

            value = e.value;
        };

        void kill() {
            hashEntryIsDead = true;
        };

        void revive() {
            hashEntryIsDead = false;
        };

        bool isEmpty() {
            return hashEntryIsEmpty;
        };

        bool isDead() {
            return hashEntryIsDead;
        };

        V getValue() {
            return value;
        };
        
        bool operator==(HashEntry const &e) {
            return this->hashEntryIsDead == false && e.hashEntryIsDead == false && e.value == this->value;
        };
};

#define HASHPRIMES_SIZE 18
const std::size_t HASHPRIMES[HASHPRIMES_SIZE]{ 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469 };

/**
 * @brief Implementation of Double Hash Set.
 * All methods (add, remove, and contains) have average time complexity of O(1)
 * The worst time complexity for these functions is O(n) when hash table is to expand.
 */
template <class T>
class DoubleHashSet : public ISet<T> {
    private:
        HashEntry<T> *hashtable;
        std::size_t hashtableSize = 0;
        
        DoubleHashSet(std::size_t size) {
            hashtable = new HashEntry<T>[HASHPRIMES[size]];
            hashtableSize = size;
        };

        /**
         * @brief Expaniding the size of the hashtable and rehash 
         * @return 
         */
        bool expandAndRehashHashtable() {
            if (hashtableSize >= HASHPRIMES_SIZE) {
                return false;
            }

            DoubleHashSet<T> *temptable = new DoubleHashSet<T>(hashtableSize + 1);

            for (int i = 0; i < getMaxSize(); i++) {
                if (!hashtable[i].isEmpty() && !hashtable[i].isDead()) {
                    T v = hashtable[i].getValue();
                    temptable->add(v);
                }
            }

            hashtableSize++;

            delete[] hashtable;
            hashtable = temptable->hashtable;
            delete temptable;

            return true;
        };

        enum SearchResult { EmptyEntry, FoundEntry, FoundDead, Undefined };
        Pair<SearchResult, std::size_t> search(HashEntry<T> * e) {
            Pair<std::size_t, std::size_t> hash = hashCodes(e->getValue());

            std::size_t index = hash.first % getMaxSize();
            std::size_t j = 1;

            std::size_t fptr = index;
            bool first_iter = true;

            while (1) {
                if (hashtable[index].isEmpty()) { // Entry in the table is available
                    return Pair<SearchResult, std::size_t>(SearchResult::EmptyEntry, index);
                } else if (hashtable[index].getValue() == e->getValue()) { // Cell in the table is occupied
                    if (hashtable[index].isDead()) { // Entry exists but was deleted
                        return Pair<SearchResult, std::size_t>(SearchResult::FoundDead, index);
                    }
                    // Entry exists and was not deleted
                    return Pair<SearchResult, std::size_t>(SearchResult::FoundEntry, index);
                } else if (!first_iter && fptr == index) { // We made a loop-around the table
                    if (expandAndRehashHashtable()) { // If expanding of the table succeded
                        return search(e);
                    }
                    // ...otherwise throw an "error"
                    return Pair<SearchResult, std::size_t>(SearchResult::Undefined, 0);
                } else {
                    // Increment the index / Perform the linear probing
                    index = (hash.first + j * hash.second) % getMaxSize();
                    j++;
                }

                first_iter = false;
            }
        };

        Pair<std::size_t, std::size_t> hashCodes(T value) {
            std::size_t h1 = std::hash<T>{}(value);
            std::size_t h2; // Should use different hash fucntions.
            // Implemented in codeforce submissions
            return Pair<std::size_t, std::size_t>(h1, MAGIC_NUMBER - (h1%MAGIC_NUMBER));
        };

        std::size_t getMaxSize() {
            return HASHPRIMES[hashtableSize];
        };

    public:
        DoubleHashSet() {
            hashtable = new HashEntry<T>[getMaxSize()];
        };

        DoubleHashSet(const DoubleHashSet<T> &dhs) : DoubleHashSet(dhs.hashtableSize) {
            this->setSize = dhs.setSize;
            std::copy(dhs.hashtable, dhs.hashtable + getMaxSize(), hashtable);
        };

        ~DoubleHashSet() {
            delete[] hashtable;
        };

        virtual void add(T value) {
            HashEntry<T> e(value);
            Pair<SearchResult, std::size_t> f = search(&e);

            if (f.first == SearchResult::EmptyEntry) {
                // Adding new element to the hashtable and extending it,
                // if the size of the hashtable exceeds half of its capacity
                hashtable[f.second] = e;

                if ((++this->setSize) * 2 >= getMaxSize()) {
                    expandAndRehashHashtable();
                }
            } else if (f.first == SearchResult::FoundDead) {
                hashtable[f.second].revive();
                ++(this->setSize);
            }
        };

        virtual void remove(T value) {
            HashEntry<T> e(value);
            Pair<SearchResult, std::size_t> f = search(&e);

            if (f.first == SearchResult::FoundEntry) {
                hashtable[f.second].kill();
                --(this->setSize);
            }
        };

        virtual bool contains(T value) {
            HashEntry<T> e(value);
            return (search(&e).first == SearchResult::FoundEntry);
        };
};
#endif
