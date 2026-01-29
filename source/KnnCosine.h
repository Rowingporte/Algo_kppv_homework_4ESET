#ifndef KNNCOSINE_H
#define KNNCOSINE_H

#include "Knn.h"

class KnnCosine : public Knn {
public:
    // Le constructeur doit accepter et transmettre la Data d'entrainement
    KnnCosine(int k, const Data& train_data);
    ~KnnCosine() = default;

    double similarity(const Sample& a, const Sample& b) const override;
    bool isSimilarity() const override { return true; } // Cosinus est une similarité
    virtual string getName() const override { return "Knn Cosine"; }
};

#endif