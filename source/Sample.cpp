#include "Sample.h"
#include <iostream>


Sample::Sample(int tag, const std::vector<double>& data) : _tag(tag), _features(data) {}

double Sample::operator[](int index) const {
    return _features[index];
}

Sample Sample::scale(double factor) const {
    std::vector<double> scaledData;
    
    for(int i = 0; i < (int)_features.size(); i++) {
        scaledData.push_back(_features[i] * factor);
    }
    
    return Sample(_tag, scaledData);
}

void Sample::toString() const {
    std::cout << "Tag : " << _tag << " | Taille: " << (int)_features.size() << std::endl;
}

const FeatureVector& Sample::getFeatures() const { return _features; }
int Sample::getTag() const { return _tag; }

int Sample::size() const { 
    return (int)_features.size(); 
}