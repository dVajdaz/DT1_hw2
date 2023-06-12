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

public:
    Record(int purchases, int id, int column);

    void buyRecord();
    void setId(int id);
    void setCol(int col);

    int getNumPurchases() const;
    int getId() const;
    int getCol() const;
};
#endif //DT1_HW2_RECORD_H
