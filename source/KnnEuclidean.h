#ifndef KNNEUCLIDEAN_H
#define KNNEUCLIDEAN_H

#include "Knn.h"

class KnnEuclidean : public Knn {
public:
    KnnEuclidean(int k, const Data& train_data); // Juste la déclaration
    virtual ~KnnEuclidean() = default;

    double similarity(const Sample& a, const Sample& b) const override; // Pas de {} ici !
    virtual string getName() const override { return "Knn Euclide"; }
}; 

#endif