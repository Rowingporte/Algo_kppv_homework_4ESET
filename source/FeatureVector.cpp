#include "FeatureVector.h"

// Constructeur par défaut
FeatureVector::FeatureVector(int dimension, double val) : _vector(dimension, val)
{
    norme(); // On calcule la norme une fois quand vecteur prêt
}

// Constructeur par vecteur de données déjà existant
FeatureVector::FeatureVector(std::vector<double> data) : _vector(data) {
    norme();
}

// Calcule racine carrée de la somme des carrés des éléments du vecteur
// Sert à calculer la similarité Cosinus dans KnnCosine
double FeatureVector::norme() const {
    double somme = 0.0;
    for (double value : _vector) {
        somme += value * value;
    }
    return std::sqrt(somme);
}

// Produit scalaire entre deux vecteurs
double FeatureVector::operator*(const FeatureVector& other) const {
    double scalaire = 0.0;
    size_t min_size = std::min(_vector.size(), other._vector.size()); // On prend taille du plus petit vecteur
    // On multiplie élément par élément des vecteurs
    for (size_t i = 0; i < min_size; ++i) {
        scalaire += _vector[i] * other._vector[i];
    }
    return scalaire;
}

// Getter + Setter
double& FeatureVector::operator[](int index) { return _vector[index]; }
// Getter
double FeatureVector::operator[](int index) const { return _vector[index]; }
size_t FeatureVector::size() const { return _vector.size(); }
const std::vector<double>& FeatureVector::getVector() const { return _vector; }