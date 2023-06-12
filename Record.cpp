//
// Created by roro1 on 12/06/2023.
//
#include "Record.h"

Record::Record(int purchases, int id, int column, int numOfCopies): purchases(purchases), id(id), column(column),
    numOfCopies(numOfCopies){};

int Record::getId() const { return id;}

void Record::buyRecord() { purchases++;}

int Record::getCol() const {return column;}

int Record::getNumPurchases() const { return purchases;}

int Record::getNumCopies() const { return numOfCopies;}

void Record::setCol(int col) {column = col;}

void Record::setId(int id) { this->id = id;}

void Record::setNumCopies(int numCopies) {numOfCopies = numCopies;}