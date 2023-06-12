//
// Created by roro1 on 12/06/2023.
//


#include "recordsCompany.h"


StatusType RecordsCompany::addCostumer(int c_id, int phone) {
    if(c_id < 0 || phone < 0) {
        return INVALID_INPUT;
    }
    Customer* toAdd;
    try {
        toAdd = new Customer(c_id, phone);
        if(customers.contains(toAdd)) {
            delete toAdd;
            return ALREADY_EXISTS;
        }

        try {
            customers.insert(*toAdd);
        }
        catch(const std::bad_alloc &) {
            delete toAdd;
            return ALLOCATION_ERROR;
        }
    }
    catch(const std::bad_alloc &) {
        delete toAdd;
        return ALLOCATION_ERROR;
    }
    return SUCCESS;


}

Output_t<int> RecordsCompany::getPhone(int c_id) {
    if(c_id < 0) { return Output_t<int>(INVALID_INPUT);}
    int phone;
    Customer* dummy;
    try {
        dummy = new Customer(c_id);
        if(!customers.contains(dummy)) {
            delete dummy;
            return Output_t<int>(DOESNT_EXISTS);
        }
        phone = customers.get(dummy)->getNumber();
        delete dummy;
    }
    catch (const std::bad_alloc &) {
        delete dummy;
        return Output_t<int>(ALLOCATION_ERROR);
    }
    return Output_t<int>(phone);

}

StatusType RecordsCompany::makeMember(int c_id) {
    if(c_id < 0) return INVALID_INPUT;
    Customer* dummy;
    try {
        dummy = new Customer(c_id);
        if(!customers.contains(dummy)) {
            delete dummy;
            return DOESNT_EXISTS;
        }
        if(customers.get(dummy)->isMember()) {
            delete dummy;
            return ALREADY_EXISTS;
        }
        customers.get(dummy)->makeMember();
        delete dummy;
    }
    catch(const std::bad_alloc &) {
        delete dummy;
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id) {
    if(c_id < 0 ) return Output_t<bool>(INVALID_INPUT);
    bool is_member;
    Customer* dummy;
    try {
        dummy = new Customer(c_id);
        if(!customers.contains(dummy)) {
            delete dummy;
            return Output_t<bool>(DOESNT_EXISTS);
        }
        is_member = customers.get(dummy)->isMember();
        delete dummy;
    }
    catch (const std::bad_alloc&) {
        delete dummy;
        return Output_t<bool>(ALLOCATION_ERROR);
    }
    return Output_t<bool>(is_member);
}

/*
StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if(c_id < 0 || r_id < 0) {
        return INVALID_INPUT;
    }
    Customer* dummy = new Customer(c_id);
    if(r_id >= numberOfRecords || !customers.contains(dummy)) {
        delete dummy;
        return DOESNT_EXISTS;
    }

} */