#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Sample.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

class Data {
    vector<Sample> _data;
    int _nbSamples;
    int _nbFeatures;
public:
    Data() : _nbSamples(0), _nbFeatures(0) {};
    void load(const string& file_name);
    void aspire_les_donnees(std::ifstream& file);
    void add(int tag, const vector<double>& features);
    void toString() const;
    int nbSamples() const { return _nbSamples; }
    Sample operator[](int index);
    Data Scale(double factor) const;
};

#endif