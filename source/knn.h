// arno qui fait
#ifndef KNN_H
#define KNN_H

#include <iostream>
using namespace std;

class Knn {
private:
    int k;
public:
    Knn(int kValue);
    ~Knn();
    virtual vector<Sample> knn::predict(Data* test_data);
    virtual knn::lazy_train(Data* trainData);
protected:
    vector<pair<double, int>> Knn::getKnn(const Sample& sample);
    virtual void Knn::predictSingle(const Sample& sample);
    virtual void Knn::similarity(Sample a, Sample b);
}