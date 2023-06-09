//
// Created by Администратор on 09.06.2023.
//

#include "Customer.h"
Customer::Customer(int id, int number,int purchases, bool membership) : id(id), number(number), purchases(purchases), membership(membership) {}

int Customer::getId() const {
    return id;
}

int Customer::getNumber() const {
    return number;
}

int Customer::getPurchases() const {
    return purchases;
}

bool Customer::isMember() const {
    return membership;
}

void Customer::makeMember() {
    membership = true;
}

void Customer::addPurchases(const int toAdd) {
    purchases += toAdd;
}

