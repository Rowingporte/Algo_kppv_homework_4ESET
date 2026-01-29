#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <fstream>
#include "Sample.h"

class Data {
private:
    std::vector<Sample> _data;
    int _nb_samples;
    int _nb_features;

public:
    Data() : _nb_samples(0), _nb_features(0) {}

    void load(const std::string& file_name);
    void aspire_les_donnees(std::ifstream& file);
    void add(int tag, const std::vector<double>& features);
    void toString() const;

    Sample& operator[](int index);
    const Sample& operator[](int index) const;

    int nbSamples() const { return _nb_samples; }
    int nbFeatures() const { return _nb_features; }
};

#endif