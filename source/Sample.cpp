#include "Sample.h"
#include <iostream>


// Création d'un Sample à partir d'une étiquette (tag) et d'un vecteur de données (features)
Sample::Sample(int tag, const std::vector<double>& data) : _tag(tag), _features(data) {}

// Surcharge de l'opérateur [] pour pouvoir acceder aux features en utilisant sample[index] au lieu de sample.getFeatures()[index]
double Sample::operator[](int index) const {
    return _features[index];
}

// Permet de modifier les valeurs du Sample en les multipliant par un facteur
Sample Sample::scale(double factor) const {
    std::vector<double> scaledData;
    
    for(int i = 0; i < (int)_features.size(); i++) {
        scaledData.push_back(_features[i] * factor);
    }

    return Sample(_tag, scaledData);
}

// Affiche le tag et la taille du sample
void Sample::toString() const {
    std::cout << "Tag : " << _tag << " | Taille: " << (int)_features.size() << std::endl;
}

// Donne le tableau de features du sample
const FeatureVector& Sample::getFeatures() const {
    return _features; 
}

// Donne quel est le tag du sample
int Sample::getTag() const {
    return _tag; 
}

//Donne le nombre d'éléments dans le Sample (nombre de features)
int Sample::size() const { 
    return (int)_features.size(); 
}