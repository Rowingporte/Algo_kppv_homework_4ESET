#ifndef FEATUREVECTOR_H
#define FEATUREVECTOR_H

#include <vector>
#include <cmath>
#include <iostream>

using std::vector;

class FeatureVector {
    vector<double> _vector;    // Stocke les features
public:
    FeatureVector(int dimension = 0, double val = 0.0) : _vector(dimension, val) { norme(); }
    FeatureVector(vector<double> data) : _vector(data) { norme(); }
    double norme() const;                                                   // Calcule la norme du vecteur (similarite cosinus)
    double operator*(const FeatureVector& other) const;                     // Produit scalaire entre deux vecteurs
    double& operator[](int index) { return _vector[index]; }                // Acces a une feacture par index (écriture)
    const double& operator[](int index) const { return _vector[index]; }    // Idem en const (lecture)
    const vector<double>& getVector() const { return _vector; }             // Vecteur des features
    size_t size() const { return _vector.size(); }           // Recupere la taille du vecteur
};

#endif