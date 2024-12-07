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
        out << "Elemento " << th.n << "\n Tamaño: " << th.max << "\n";
        for (int i = 0; i < th.max; i++) {
            out << " Cubeta " << i << "\n";
            out << "Lista: " << th.table[i] << "\n";
        }
        out << "\n";
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
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos != -1) {
            throw std::runtime_error("Clave '" + key + "' ya existe");
        }
        table[index].prepend(TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave '" + key + "' no encontrada");
        }
        return table[index].get(pos).value;
    }

    V remove(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave '" + key + "' no encontrada");
        }
        V removedValue = table[index].get(pos).value;
        table[index].remove(pos);
        n--;
        return removedValue;
    }

    int entries() override {
        return n;
    }
};

#endif

