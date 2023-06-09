//
// Created by Администратор on 09.06.2023.
//

#ifndef UNTITLED_CUSTOMER_H
#define UNTITLED_CUSTOMER_H


class Customer {
private:
    int id;
    int number;
    int purchases;

    bool membership;
public:
    Customer(int id, int number,int purchases = 0, bool membership = false);

    Customer(const Customer &toCopy) = default;

    ~Customer() = default;

    int getId() const;

    bool isMember() const;
    void makeMember();
};

#endif //UNTITLED_CUSTOMER_H
