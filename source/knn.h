#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cmath>
#include <Sample.h>
#include <Data.h>

using std::vector;
using std::pair;
using std::map;

class Knn {
    int k;
    Data _lazy_train;
public:
    Knn(int kValue) : k(kValue) {};
    ~Knn() {};
    virtual vector<Sample> predict(Data* test_data);
protected:
    vector<pair<double, int>> getKnn(const Sample& sample);
    virtual void predictSingle(const Sample& sample);
    virtual double similarity(Sample a, Sample b);
};

#endif