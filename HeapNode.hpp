#pragma once
#include <iostream>
using namespace std;
#include <limits>

class HeapNode {
public:
    HeapNode(float key, int indexInGraph) {
        myKey = key;
        myIndexInGraph = indexInGraph;
    }
    float getKey();
    unsigned int getIndexInGraph(int currentIteration);
    void setIndex(unsigned int index);
    void setKey(float key);

private:
    int usedInIteration = -1;
    float myKey = numeric_limits<float>::max();
    int myIndexInGraph = -1;
};