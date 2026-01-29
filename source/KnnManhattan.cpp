#include "KnnManhattan.h"

// Constructeur
KnnManhattan::KnnManhattan(int k, const Data& train_data) : Knn(k, train_data) {}

// Distance de Manhattan : Somme des valeurs absolues des différences
double KnnManhattan::similarity(const Sample& a, const Sample& b) const {
    double distance = 0.0;
    int n = a.size();

    for (int i = 0; i < n; i++) {
        // std::abs pour la valeur absolue |a - b|
        distance += std::abs(a[i] - b[i]);
    }

    return distance;
}