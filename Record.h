//
// Created by roro1 on 12/06/2023.
//

#ifndef DT1_HW2_RECORD_H
#define DT1_HW2_RECORD_H

class Record {
private:
    int purchases;
    int id;
    int column;
    int numOfCopies;
public:
    Record(int id, int numOfCopies, int column = 0,  int purchases = 0);
    Record() = default;
    void buyRecord();
    void setId(int id);
    void setCol(int col);
    void setNumCopies(int numCopies);

    int getNumPurchases() const;
    int getId() const;
    int getCol() const;
    int getNumCopies() const;
};
#endif //DT1_HW2_RECORD_H
