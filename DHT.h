//
// Created by Администратор on 09.06.2023.
//

#ifndef UNTITLED_DHT_H
#define UNTITLED_DHT_H

#include <new>
#include "Customer.h"
#include "AVL.h"

const int initial = 10;

template<class T>
class CompareById {
public:
    CompareById() = default;

    ~CompareById() = default;

    int operator()(const T &a, const T &b) const {
        return a.getId() - b.getId();
    }
};

class DHT {
    public:
    AVL<Customer, CompareById<Customer>>* array;


    int capacity;
    int occupancy;

    const int expansion;
    //const int shrinkage;

    DHT(const int &expansion_rate): capacity(initial),
                                    occupancy(0),
                                    expansion(expansion_rate)
                                    //shrinkage(shrinkage_rate)
    {
        for (int counter = 0; counter < initial; counter++) {
            array[counter] = AVL<Customer, CompareById<Customer>>();
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

    int hashFunction(const int& id) const;

    bool Find(const int &id) const;

    void Insert(Customer& customer);
    //void Remove(const int &id);

    void newArray(const int& newCapacity);

};

#endif //UNTITLED_DHT_H
