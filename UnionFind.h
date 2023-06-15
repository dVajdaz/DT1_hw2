//
// Created by roro1 on 12/06/2023.
//

#ifndef DT1_HW2_UNIONFIND_H
#define DT1_HW2_UNIONFIND_H
#include "iostream"

template<typename T>
class UnionFind {
private:
    int groupNum; //Number of groups, which is also the number of elements
    T* elements; //An array containing all the elements in the data structure
    int* sizes; //An  array containing all the sizes of groups
    int* parents; //An array in which parents[i] contains the index of the element
    int* bottom;
    //int* heights;
    int* extras;
    void merge(int smallerGroupRoot, int largerGroupRoot) {
        parents[smallerGroupRoot] = largerGroupRoot;
        sizes[largerGroupRoot] += sizes[smallerGroupRoot];
    }

public:

    UnionFind() = default;

    UnionFind(int groupNum) : groupNum(groupNum),
        elements(new T(groupNum)) , sizes(new int[groupNum]), parents(new int[groupNum]),bottom(new int[groupNum]) ,
         extras(new int[groupNum])
    {
        for (int i = 0; i < groupNum; i++) {
            sizes[i] = elements[i].getNumCopies();
            parents[i] = i;
            bottom[i] = i;
            //heights[i] = elements[i].getNumCopies();
            extras[i] = 0;
        }
    };

    void makeNewSet(int size) {
        delete[] elements;
        delete[] sizes;
        delete[] parents;
        delete[] bottom;
        //delete[] heights;
        delete [] extras;
        groupNum = size;
        elements = new T[size];
        sizes = new int[size];
        parents = new int[size];
        //heights = new int[size];
        bottom = new int[size];
        extras = new int[size];
        for (int i = 0; i < groupNum; i++) {
            sizes[i] = elements[i].getNumCopies();
            parents[i] = i;
            //heights[i] = elements[i].getNumCopies();
            extras[i] =  0;
            bottom[i] = i;
        }
    }
    void put(int i, const T& element) {
        elements[i] = element;
        sizes[i] = elements[i].getNumCopies();
        parents[i] = i;
        //heights[i] = elements[i].getNumCopies();
        extras[i] =  0;
    }

    T& get(int index) { return elements[index];}

    int find(int index) {
        /*
        if(parents[index] == index) { return index;}
        parents[index] = find(parents[index]);
        return parents[index]; */
        int sumExtra = 0, toSubtract = 0, startIndex = index, oldExtra = 0;
        while(parents[index] != index) {
            sumExtra += extras[index];
            index = parents[index];
        }
        while (startIndex != index) {
            int temp = parents[startIndex];
            oldExtra = extras[startIndex];
            extras[startIndex] = sumExtra - toSubtract;
            toSubtract += oldExtra;
            parents[startIndex] = index;
            startIndex = temp;
        }
        return index;
    }

    void unite(int index1, int index2) {
        int groupRoot1 = find(index1);
        int groupRoot2 = find(index2);
        if(sizes[groupRoot1] > sizes[groupRoot2]) {
            merge(groupRoot2, groupRoot1);

        }
        else {
            merge(groupRoot1, groupRoot2);
        }
        find(index1);
        find(index2);
    }

    bool isSameGroup(int index1, int index2) {
        return find(index1) == find(index2);
    }
    void putOnTop(int index1 , int index2) {
        int groupRoot1 = find(index1);
        int groupRoot2 = find(index2);
        if(sizes[groupRoot1] > sizes[groupRoot2]) {
            extras[groupRoot1] += sizes[groupRoot2];
            extras[groupRoot2] -= extras[groupRoot1];
            bottom[groupRoot1] = bottom[groupRoot2];
        }
        else {
            extras[groupRoot1] += (sizes[groupRoot2] - extras[groupRoot2]);
        }
        unite(groupRoot1, groupRoot2);
    }

    int getColumn(int index) { return bottom[find(index)];}
    int getHeight(int index) {
        if(parents[index] == index) {
            return extras[index];
        }
        return extras[index] + getHeight(parents[index]);
    }
    int getSize() const {return groupNum;}


    ~UnionFind() {
        delete[] elements;
        delete[] sizes;
        delete[] parents;
        //delete[] heights;
        delete [] extras;
        delete [] bottom;
    }

};






#endif //DT1_HW2_UNIONFIND_H
