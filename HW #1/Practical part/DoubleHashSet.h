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

template <class T>
class DoubleHashSet : public ISet<T> {
    private:
        HashEntry<T> *hashtable;
        std::size_t hashtableSize = 128;
        
        void expandHashtable() {
            HashEntry<T> *temp = new HashEntry<T>[hashtableSize * 2];

            std::size_t i = 0;
            while (i < hashtableSize) {
                temp[i] = hashtable[i];
                ++i; 
            }

            hashtableSize *= 2;

            delete[] hashtable;
            hashtable = temp;
        };

        Pair<bool, std::size_t> find(HashEntry<T> * e) {
            Pair<std::size_t, std::size_t> hash = hashCodes(e->getValue());
            
            std::size_t index = hash.first % hashtableSize;
            std::size_t j = 0;

            while (1) {
                if (hashtable[index].isEmpty()) {
                    return Pair<bool, std::size_t>(false, 0);
                } else if (hashtable[index] == (*e)) {
                    return Pair<bool, std::size_t>(true, index);
                } else {
                    index = (hash.first + j * hash.second) % hashtableSize;
                    j++;
                }
            }
        };

        Pair<std::size_t, std::size_t> hashCodes(T value) {
            return Pair<std::size_t, std::size_t>(std::hash<T>{}(value), (MAGIC_NUMBER * std::hash<T>{}(value)) % SIZE_MAX);
        };

    public:
        DoubleHashSet() {
            hashtable = new HashEntry<T>[hashtableSize];
        };
        
        DoubleHashSet(std::size_t size) {
            hashtable = new HashEntry<T>[size];
        };

        ~DoubleHashSet() {
            delete[] hashtable;
        };

        virtual void add(T value) {
            HashEntry<T> e(value);
            Pair<bool, std::size_t> f = find(&e);

            if (!f.first) {
                // Adding new element to the hashtable and extending it,
                // if the size of the hashtable exceeds half of its capacity
                hashtable[f.second] = e;

                if (++this->setSize >= hashtableSize>>1) {
                    expandHashtable();
                }
            }
        };

        virtual void remove(T value) {
            HashEntry<T> e(value);
            Pair<bool, std::size_t> f = find(&e);

            if (f.first) {
                hashtable[f.second].kill();
                --(this->setSize);
            }
        };

        virtual bool contains(T value) {
            HashEntry<T> e(value);
            return find(&e).first;
        };
};
#endif
