//
// Created by Администратор on 09.06.2023.
//

#ifndef UNTITLED_DHT_H
#define UNTITLED_DHT_H

#include <new>
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

template<class T>
class Reinsert;

template<class T>
class DHT {
    int capacity, occupancy;
    //const int expansion;
    int expansion;
    //const int shrinkage;

public:
    DHT(const int capacity = 16, int expansion_rate = 2):  array(new AVL<T, CompareById<T>>[capacity]),
                                                                    capacity(capacity),
                                                                    occupancy(0),
                                                                    expansion(expansion_rate)
                                                                    //shrinkage(shrinkage_rate)
     {}

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

            Reinsert<T> reinsert(this);
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


template<class T>
class Reinsert {
    DHT<T> *hashTable;
public:
    explicit Reinsert(DHT<T> *DHT) : hashTable(DHT) {};
    ~Reinsert() = default;

    bool operator()(T& a) {
        hashTable->insert(a);
        return true;
    }
};

#endif //UNTITLED_DHT_H
