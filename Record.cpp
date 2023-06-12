//
// Created by roro1 on 12/06/2023.
//
#include "Record.h"

Record::Record(int purchases, int id, int column): purchases(purchases), id(id), column(column) {};

int Record::getId() const { return id;}

void Record::buyRecord() { purchases++;}

int Record::getCol() const {return column;}

int Record::getNumPurchases() const { return purchases;}

void Record::setCol(int col) {column = col;}

void Record::setId(int id) { this->id = id;}