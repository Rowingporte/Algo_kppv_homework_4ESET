#ifndef KNNCOSINE_H
#define KNNCOSINE_H

#include "Knn.h"

class KnnCosine : public Knn {
public:
    // Constructeur transmet les infos au constructeur de Knn
    KnnCosine(int k, const Data& train_data);
    ~KnnCosine() = default;

    // Surcharge de la méthode virtuelle similarity de la classe mère.
    double similarity(const Sample& a, const Sample& b) const override;

    // Indique si la mesure est une similarité ou une distance.
    bool isSimilarity() const override { return true; } // Cosinus est une similarité

    // Pour le rapport
    virtual string getName() const override { return "Knn Cosine"; }
};

#endif