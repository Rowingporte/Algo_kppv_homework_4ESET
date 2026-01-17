// arno qui fait
#ifndef SAMPLE_H
#define SAMPLE_H

#include <iostream>
using namespace std;

class Sample {
private:
    int _tag;
    vector<double> _features;
public:
    Sample(int tagValue, const vector<double>& featurevalues);
    int operator[](int index);
    int get_tag() const;
    vector<double> get_features() const;
    int set_features(const vector<double>& feature);
    void toString() const;
    Sample Scale(Sample s, double factor);
}
