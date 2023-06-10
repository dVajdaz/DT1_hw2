//
// Created by Администратор on 09.06.2023.
//

#include "DHT.h"

int DHT::hashFunction(const int &id) const {
    return id % capacity;
}

bool DHT::Find(const int &id) const
{
    Customer dummy = new Customer(id);

    bool ans = (array[hashFunction(id)].find(dummy) != nullptr);

    delete dummy;
    return ans;
}

void DHT::Insert(Customer& customer)
{
    if (occupancy + 1 == capacity){
        capacity *= expansion;
        newArray(capacity);
    }

    array[hashFunction(customer.getId())].insert(customer);

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
        if(array[i])
           rehashTree(array[i], newArray);
           //delete array[i];   //NOT SURE IF NEEDED SINCE CALLING delete[] array AFTER
    }

    delete[] array;
    array = newArray;
}

void DHT:rehashTree(AVL<Customer, CompareById<Customer> tree, int* newArray){
        if (!(tree.root))
            return;

        rehashTree(tree.root->right, newArray);
        *newArray[hashFunction(tree.root.obj->getId())].insert(tree.root.obj);
        rehashTree(tree.root->left, newArray);
};