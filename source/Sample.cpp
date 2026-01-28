#include "Sample.h"

// Constructeur
Sample::Sample(int tag, const std::vector<double>& data) : _tag(tag), _features(data) {}

// Surcharge [] : Délègue la demande à l'objet FeatureVector interne
double Sample::operator[](int index) const {
    return _features[index];
}

// Renvoie nouveau objet Sample avec valeurs multipliées par le facteur
Sample Sample::scale(double factor) const {
    std::vector<double> scaledData;
    
    // Multiplication des données par le facteur
    for(size_t i = 0; i < _features.size(); i++) {
        scaledData.push_back(_features[i] * factor);
    }
    
    return Sample(_tag, scaledData);
}

// Affichage dans la console
void Sample::toString() const {
    std::cout << "Tag : " << _tag << " | Taille: " << _features.size() << std::endl;
}

// Getters
const FeatureVector& Sample::getFeatures() const { return _features; }
int Sample::getTag() const { return _tag; }
size_t Sample::size() const { return _features.size(); }
