/*
 * hashtable.h
 *
 * A basic hashtable implementation.  This hashtable uses vectors,
 * rather than linked lists, to implement chaining.
 *
 * Author: <your name here>
 */

#ifndef SOMETHING_RANDOM
#define SOMETHING_RANDOM

#include <algorithm>
#include <functional>   // for std::hash
#include <vector>

using namespace std;

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable() : tableSize(4), numElements(0) {
        table.resize(tableSize);
    }

    // basic hashset operations
    void insert(const T& key) {
        if (!this->contains(key)) {
            if (this->load_factor() + (1 / tableSize) >= 0.75) resize();
            table.at(hash(key) % tableSize).push_back(key);
            numElements++;
        }
    }

    void remove(const T& key) {
        if (this->contains(key)) {
            auto& chain = table.at(hash(key) % tableSize);
            chain.erase(find(chain.begin(), chain.end(), key));
            numElements--;
        }
    }

    bool contains(const T& key) {
        const auto& chain = table.at(hash(key) % tableSize);
        for (const auto& elem : chain) if (elem == key) return true;
        return false;
    }

    size_t size() const { return numElements; }

    // diagnostic functions
    double load_factor() {
        return numElements / static_cast<double>(tableSize);
    }

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

    // Returns an integer representing the number of comparison operations performed in testing for containment
    int count_comparisons(const T& key) {
        const auto& chain = table.at(hash(key) % tableSize);
        int counter = 0;
        for (const auto& elem : chain) {
            counter++;
            if (elem == key) break;
        }

        return counter;
    }

private:
    size_t tableSize;
    vector<vector<T>> table;
    size_t numElements;

    void resize() {
        tableSize *= 2;
        vector<vector<T>> newTable(tableSize);
        for (const auto& chain : table) {
            for (const auto& elem : chain) {
                newTable.at(hash(elem) % tableSize).push_back(elem);
            }
        }

        table.swap(newTable);
    }
};
#endif
