#include "Sample.h"

void Sample::toString() const {
    cout << "Tag: " << this->get_tag() << endl;
    cout << "Features: ";
    for(double feature : this->get_features()) { cout << feature << " ";}
};

double Sample::operator[](int index) {
    if (index < 0 || index >= _features.size()) { throw std::out_of_range("Index hors des limites"); }
    return _features[index];
}

Sample Sample::Scale(Sample s, double factor) const {
    vector<double> scaledFeatures;
    for(double feature : s.get_features()){
        scaledFeatures.push_back(feature * factor);
    }
    return Sample(s.get_tag(), scaledFeatures);
}
