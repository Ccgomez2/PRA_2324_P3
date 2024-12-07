#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../practica1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << "Cubeta " << i << ": " << th.table[i] << std::endl;
        }
        return out;
    }

    V operator[](std::string key) {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        return table[index].get(pos).value;
    }

    void insert(std::string key, V value) override {
        int index = h(key);
        TableEntry<V> entry(key, value);
        table[index].append(entry);
        n++;
    }

    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        return table[index].get(pos).value;
    }

    V remove(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        table[index].remove(pos);
        n--;
        return entry.value;
    }

    int entries() override {
        return n;
    }
};

#endif

