//
// Created by roro1 on 12/06/2023.
//

#ifndef DT1_HW2_UNIONFIND_H
#define DT1_HW2_UNIONFIND_H


template<typename T>
class UnionFind {
private:
    int groupNum; //Number of groups, which is also the number of elements
    T* elements; //An array containing all the elements in the data structure
    int* sizes; //An  array containing all the sizes of groups
    int* parents; //An array in which parents[i] contains the index of the element

    void merge(int smallerGroupRoot, int largerGroupRoot) {
        parents[smallerGroupRoot] = largerGroupRoot;
        sizes[largerGroupRoot] += sizes[smallerGroupRoot];
        sizes[smallerGroupRoot] += sizes[largerGroupRoot];
    }
    /*
    struct RootNode {
        int index;
        T& value;
    }; */
public:

    UnionFind() = default;

    UnionFind(int groupNum) : groupNum(groupNum),
        elements(new T(groupNum)) , sizes(new int[groupNum]), parents(new int[groupNum])
    {
        for (int i = 0; i < groupNum; i++) {
            sizes[i] = 1;
            parents[i] = i;
        }
    };

    void makeNewSet(int size) {
        delete[] elements;
        delete[] sizes;
        delete[] parents;
        groupNum = size;
        elements = new T[size];
        sizes = new int[size];
        parents = new int[size];
        for (int i = 0; i < groupNum; i++) {
            sizes[i] = 1;
            parents[i] = i;
        }
    }
    void put(int index, const T& element) {
        elements[index] = element;
    }

    T& get(int index) { return elements[index];}

    int find(int index) {
        if(parents[index] == index) { return index;}
        parents[index] = find(parents[index]);
        return parents[index];
    }

    void unite(int index1, int index2) {
        int groupRoot1 = this->find(index1);
        int groupRoot2 = this->find(index2);
        if(sizes[groupRoot1] > sizes[groupRoot2])
            merge(groupRoot2, groupRoot1);
        else
            merge(groupRoot1, groupRoot2);

    }

    int getSize() const {return groupNum;}

    ~UnionFind() {
        delete[] elements;
        delete[] sizes;
        delete[] parents;
    }

};






#endif //DT1_HW2_UNIONFIND_H
