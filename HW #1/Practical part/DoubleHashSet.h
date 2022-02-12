#ifndef _DOUBLE_HASH_SET_H_
#define _DOUBLE_HASH_SET_H_

#include "ISet.h"
#include <cstring>
#include <functional>

#define MAGIC_NUMBER 5231

template<class F, class S>
class Pair {
    public:
        F first;
        S second;

        Pair() {
            first = {}, second = {};
        };

        Pair(F f, S s) {
            first = f, second = s;
        };

        bool operator==(Pair p) {
            return p.first == first && p.second == second;
        };
};

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

        bool isEmpty() {
            return hashEntryIsEmpty;
        };

        bool isDead() {
            return hashEntryIsDead;
        };

        V getValue() {
            return value;
        };
        
        bool operator==(HashEntry e) {
            return hashEntryIsDead == false && e.value == value;
        };
};

#define HASHPRIMES_SIZE 18
const std::size_t HASHPRIMES[HASHPRIMES_SIZE]{ 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469 };

template <class T>
class DoubleHashSet : public ISet<T> {
    private:
        HashEntry<T> *hashtable;
        std::size_t hashtableSize = 0;
        
        DoubleHashSet(std::size_t size) {
            hashtable = new HashEntry<T>[HASHPRIMES[size]];
            hashtableSize = size;
        };
        
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
            return true;
        };

        enum SearchResult { EmptyEntry, FoundEntry, Undefined };
        Pair<SearchResult, std::size_t> search(HashEntry<T> * e) {
            Pair<std::size_t, std::size_t> hash = hashCodes(e->getValue());

            std::size_t index = hash.first % getMaxSize();
            std::size_t j = 1;

            std::size_t fptr = index;
            bool first_iter = true;

            while (1) {
                if (hashtable[index].isEmpty()) {
                    return Pair<SearchResult, std::size_t>(SearchResult::EmptyEntry, index);
                } else if (hashtable[index] == (*e)) {
                    return Pair<SearchResult, std::size_t>(SearchResult::FoundEntry, index);
                } else if (!first_iter && fptr == index) {
                    if (expandAndRehashHashtable()) {
                        return search(e);
                    }
                    return Pair<SearchResult, std::size_t>(SearchResult::Undefined, 0);
                } else {
                    index = (hash.first + j * hash.second) % getMaxSize();
                    j++;
                }

                first_iter = false;
            }
        };

        Pair<std::size_t, std::size_t> hashCodes(T value) {
            std::size_t h = std::hash<T>{}(value);
            return Pair<std::size_t, std::size_t>(h, (MAGIC_NUMBER * h) % SIZE_MAX);
        };

        std::size_t getMaxSize() {
            return HASHPRIMES[hashtableSize];
        };

    public:
        DoubleHashSet() {
            hashtable = new HashEntry<T>[getMaxSize()];
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

                if ((++this->setSize) / getMaxSize() >= 0.75 + (hashtableSize / HASHPRIMES_SIZE) * 0.25) {
                    expandAndRehashHashtable();
                }
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
            return search(&e).first;
        };
};
#endif
