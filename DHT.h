//
// Created by Администратор on 09.06.2023.
//

#ifndef UNTITLED_DHT_H
#define UNTITLED_DHT_H

#include <new>
#include <vector>
#include "AVL.h"

template<class T>
class CompareById {
public:
    CompareById() = default;

    ~CompareById() = default;

    int operator()(const T &a, const T &b) const {
        return a.getId() - b.getId();
    }
};

template<class T, class Comparator>
class Reinsert;

template<class T>
class DHT {
    int capacity, occupancy;
     int expansion;
    //const int shrinkage;

public:
    DHT(const int capacity = 16, int expansion_rate = 2):           array(new AVL<T, CompareById<T>>[capacity]),
                                                                    capacity(capacity),
                                                                    occupancy(0),
                                                                    expansion(expansion_rate)
                                                                    //shrinkage(shrinkage_rate)
     {
         for (int i = 0; i < capacity; ++i) {
             array[i] = AVL<T, CompareById<T>>();
         }
     }

/*
    DHT(const DHT &toCopy): array(new  int[toCopy.capacity]),   //NOT SURE IF NEEDED
                            capacity(toCopy.capacity),
                            occupancy(toCopy.occupancy),
                            expansion(toCopy.expansion)
                            //shrinkage(toCopy.shrinkage)

    {
        for (int i = 0; i < toCopy.occupancy; i++)
        {
            array[i] = toCopy.array[i];
        }
    }
*/

    ~DHT() {
        delete[] array;
    }

    int hashFunction(const int& id){
        return id % capacity;
    }

    bool contains(T* dummy){
        return array[hashFunction(dummy->getId())].find(dummy) != nullptr;
    }

    T* get(T* dummy){
        return array[hashFunction(dummy->getId())].find(dummy);
    }

    void insert(T& toAdd){
            if (occupancy + 1 == capacity)
                newArray();

            array[hashFunction(toAdd.getId())].insert(toAdd);

            occupancy++;
    }

    void newArray(){
        auto* oldData = array;
        int prevOccupancy = occupancy;

        capacity *= expansion;
        try
        {
            array = new AVL<T, CompareById<T>>[capacity];
            occupancy = 0;

            Reinsert<T, CompareById<T>> reinsert(this);
            for (int i = 0; i < capacity/expansion; i++)
            {
                oldData[i].runInOrder(reinsert);
                //oldData[i].setObjectDelete();
            }
        } catch (const std::bad_alloc &e)
        {
            delete[] array;
            array = oldData;
            capacity /= expansion;
            occupancy = prevOccupancy;

            throw e;
        }
        delete[] oldData;
    }

    int getCapacity() const{
        return capacity;
    }

    int getOccupancy() const{
        return occupancy;
    }

    AVL<T, CompareById<T>> *array;
};

template<class T, class Comparator>
class Scan {
    std::vector<double> *vec;
    AVL<T, Comparator> *tree;
    int i1, i2;
    double amount;
public:
    Scan(std::vector<double> *vec, AVL<T, Comparator> *tree, int i1, int i2, double amount) : vec(vec), tree(tree), i1(i1), i2(i2), amount(amount) {};
    ~Scan() = default;

    bool operator()(T& a) {
        int id = a.getId();
        double value = tree->calculateExtra(id, tree->root);
        if (id >= i1 && id <= i2) {
            value += amount;
        }
        vec->push_back(value);
        return true;
    }
};

template<class T, class Comparator>
class Reinsert {
    DHT<T> *hashTable;
public:
    Reinsert(DHT<T> *DHT) : hashTable(DHT) {};
    ~Reinsert() = default;

    bool operator()(T& a) {
        hashTable->insert(a);
        return true;
    }
};

#endif //UNTITLED_DHT_H
