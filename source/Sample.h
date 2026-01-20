#ifndef SAMPLE_H
#define SAMPLE_H

#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Sample {
private:
    int _tag;
    vector<double> _features;
public:
    Sample(int tagValue, const vector<double>& featurevalues) : _tag(tagValue), _features(featurevalues) {};
    int get_tag() const { return _tag; };
    vector<double> get_features() const { return _features; };
    void toString() const;
    double operator[](int index);
    Sample Scale(Sample s, double factor) const;
    //int set_features(const vector<double>& feature);
};

#endif
