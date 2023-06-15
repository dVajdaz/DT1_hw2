//
// Created by roro1 on 12/06/2023.
//


#include "recordsCompany.h"

RecordsCompany::RecordsCompany(): records(UnionFind<Record>()) , customers(DHT<Customer>()) {
    numberOfRecords = 0;
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
        records.makeNewSet(number_of_records);
        for(int r_id = 0; r_id < number_of_records; r_id++) {
            Record toInsert = Record(0, r_id, 0, records_stocks[r_id]);
            records.put(r_id, toInsert);
        }

}

RecordsCompany::~RecordsCompany() {
    for (int i = 0; i < customers.getCapacity(); ++i) {
        customers.array[i].setObjectDelete();
    }

}

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
    if(c_id < 0) return Output_t<bool>(INVALID_INPUT);
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


StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if(c_id < 0 || r_id < 0) {
        return INVALID_INPUT;
    }
    int numOfPurchases;
    Customer* dummy;
    try {
        dummy = new Customer(c_id);
        if (r_id >= numberOfRecords || !customers.contains(dummy)) {
            delete dummy;
            return DOESNT_EXISTS;
        }
        numOfPurchases = records.get(r_id).getNumPurchases();
        records.get(r_id).buyRecord();
        if(customers.get(dummy)->isMember())
            customers.get(dummy)->addPurchases(100 + numOfPurchases);
        delete dummy;
    }
    catch(const std::bad_alloc& ) {
        delete dummy;
        return ALLOCATION_ERROR;
    }

}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount) {
    if(amount <= 0 || c_id1 < 0 || c_id2 < 0 || c_id1 > c_id2) return INVALID_INPUT;
    for(int i =0; i < customers.getCapacity(); i++) {
        if(customers.array[i].size != 0) {
            customers.array[i].addPrize(c_id1, c_id2, amount);
        }
    }
    return SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id) {
    if(c_id < 0) { return Output_t<double>(INVALID_INPUT);}
    Customer* dummy;
    try {
        dummy = new Customer(c_id);
        if(!customers.get(dummy) || !customers.get(dummy)->isMember()) return Output_t<double>(DOESNT_EXISTS);
        return Output_t<double>(customers.get(dummy)->getPurchases() -
                customers.array[customers.hashFunction(c_id)].calculateExtra(c_id, customers.array[customers.hashFunction(c_id)].root));
    }
    catch (const std::bad_alloc&) {
        delete dummy;
        return Output_t<double>(ALLOCATION_ERROR);
    }
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if(r_id1 < 0 || r_id2 < 0) { return INVALID_INPUT;}
    if(r_id2 >= numberOfRecords || r_id1 >= numberOfRecords) {
        return DOESNT_EXISTS;
    }
    if(records.isSameGroup(r_id2, r_id1)) return FAILURE;
    records.putOnTop(r_id1, r_id2);
    return SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    *column = records.getColumn(r_id);
    *hight = records.getHeight(r_id);
}



