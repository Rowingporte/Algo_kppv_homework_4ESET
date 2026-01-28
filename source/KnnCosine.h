#ifndef KNNCOSINE_H
#define KNNCOSINE_H

#include "Knn.h"

class KnnCosine : public Knn {
public:
    // Constructeur
    KnnCosine(int k, const Data& data);

    // Destructeur
    ~KnnCosine() = default;

    // Surcharge des méthodes virtuelles
    // On remplace le calcul de distance Euclidienne par la similarité Cosinus
    double similarity(const Sample& a, const Sample& b) const override;

    // Pour le tri (false dans knn, true dans knnCosine)
    bool isSimilarity() const override { return true; } 
};

#endif