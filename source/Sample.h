#ifndef SAMPLE_H
#define SAMPLE_H

#include <iostream>
#include <vector>
#include "FeatureVector.h"

class Sample {
private:
    int _tag;                // Etiquette (chiffre) réel déterminé
    FeatureVector _features; // Objet FeatureVector contenant les données

public:
    // Constructeur
    Sample(int tag, const std::vector<double>& data);

    // Surcharge [] : Permet d'écrire sample[0] au lieu de sample.get_features()[0]
    double operator[](int index) const;

    // Crée nouveau sample avec valeurs multipliées
    // Permet de ramener toutes les caractéristiques dans le même ordre de grandeur
    Sample scale(double factor) const;
    
    // Afficher dans console
    void toString() const;
    
    
    // Getters
    const FeatureVector& getFeatures() const;
    int getTag() const;   
    int size() const;
};

#endif