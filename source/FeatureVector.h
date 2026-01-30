#ifndef FEATUREVECTOR_H
#define FEATUREVECTOR_H

#include <vector>
#include <cmath>
#include <iostream>

using std::vector;

class FeatureVector {
    vector<double> _vector; // Stocke les valeurs réelles des caractéristiques
public:
    // Créer vecteur avec dimension et valeur par défaut
    FeatureVector(int dimension = 0, double val = 0.0) : _vector(dimension, val) {}

    // Crée un FeatureVector à partir d'un std::vector existant
    FeatureVector(vector<double> data) : _vector(data) { norme(); } 

    // Calcule la norme du vecteur (pour Cosine après)
    double norme() const;   
       
    // Surcharge de l'opérateur * pour calculer le prouit scalaire
    double operator*(const FeatureVector& other) const;  
    
    // Surcharge de l'opérateur [] pour en écriture
    double& operator[](int index) { return _vector[index]; }  

    // Surcharge de l'opérateur [] pour en lecture
    const double& operator[](int index) const { return _vector[index]; }  
    
    // Getter du std::vector
    const vector<double>& getVector() const { return _vector; }   
    
    // Dimension du vecteur
    size_t size() const { return _vector.size(); }
};

#endif