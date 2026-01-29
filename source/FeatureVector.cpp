#include "FeatureVector.h"

// Calcule la norme du vecteur (similarite cosinus)
double FeatureVector::norme() const {
    double somme = 0.0;
    for (double value : _vector) { somme += value * value; }
    return std::sqrt(somme);
}

// Produit scalaire entre deux vecteurs
double FeatureVector::operator*(const FeatureVector& other) const {
    double scalaire = 0.0;
    size_t min_size = std::min(_vector.size(), other._vector.size());                       // On prend taille du plus petit vecteur
    for (size_t i = 0; i < min_size; ++i) { scalaire += _vector[i] * other._vector[i]; }    // Somme des produits
    return scalaire;
}