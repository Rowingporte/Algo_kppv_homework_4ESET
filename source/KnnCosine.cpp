#include "KnnCosine.h"
#include <iostream>

// Constructeur : On passe les arguments au constructeur de la classe mère
KnnCosine::KnnCosine(int k, const Data& data) : Knn(k, data) {}

// On remplace le calcul de distance Euclidienne par la similarité Cosinus
double KnnCosine::similarity(const Sample& a, const Sample& b) const {
    // On récupère les features des deux sample
    const FeatureVector& fa = a.getFeatures();
    const FeatureVector& fb = b.getFeatures();

    // On calcule longueur
    double normeA = fa.norme();
    double normeB = fb.norme();

    // Sécurité pour la division par 0
    if (normeA == 0 || normeB == 0) {
        return 0;
    }
    // Résultat final
    return (fa * fb) / (normeA * normeB);
}