//
// Created by Администратор on 09.06.2023.
//

#include "DHT.h"

int DHT::hashFunction(const int &id) const {
    return id % capacity;
}

bool DHT::Find(const int &id) const
{
    //call hashFunction to get the index -> call find function of the structure stored in the index
    return true;
}

void DHT::Insert(int customer)
{
    if (occupancy + 1 == capacity){
        capacity *= expansion;
        newArray(capacity);
    }

    //array[hashFunction(customer)] = customer;   //TODO: Overload operator = for AVL tree

    occupancy++;
}

void DHT::newArray(const int &newCapacity) {
    AVL<Customer,CompareById<Customer>> * newArray;

    try
    {
        newArray = new AVL<Customer, CompareById<Customer>>[newCapacity];
    } catch (const std::bad_alloc &e)
    {
        capacity /= expansion;
        delete newArray;
        throw e;
    }

    for (int i = 0; i < capacity/expansion; i++)
    {
        //TODO: Copy each object of the table into the new array using updated hashFunction
    }

    delete[] array;
    array = newArray;
}