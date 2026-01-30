#include "KnnCosine.h"
#include <iostream>

// On transmet train_data à la classe mère Knn
KnnCosine::KnnCosine(int k, const Data& train_data) : Knn(k, train_data) {} // Appelle constructeur classe mère

// Polymorphisme de classe Knn
// Prend deux Sample en entrée (test et train) pour calculer leur ressemblance
double KnnCosine::similarity(const Sample& a, const Sample& b) const {
    const FeatureVector& fa = a.getFeatures();
    const FeatureVector& fb = b.getFeatures();

    double normeA = fa.norme();
    double normeB = fb.norme();

    if (normeA == 0 || normeB == 0) return 0;
    
    // Utilisation de la surcharge * et de norme() pour le calcul
    return (fa * fb) / (normeA * normeB);
}