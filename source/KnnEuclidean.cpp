#include "KnnEuclidean.h"
#include <cmath>

KnnEuclidean::KnnEuclidean(int k, const Data& train_data) 
    : Knn(k, train_data) 
{
}

double KnnEuclidean::similarity(const Sample& a, const Sample& b) const {
    double somme = 0.0;
    for (int i = 0; i < a.size(); i++) {
        double diff = a[i] - b[i];
        somme += diff * diff;
    }
    return std::sqrt(somme);
}