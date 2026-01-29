#ifndef KNN_H
#define KNN_H

#include "Data.h"
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

class Knn {
protected:
    int _k;
    const Data& _train_data;

    // Méthode de calcul de proximité
    virtual double similarity(const Sample& a, const Sample& b) const = 0;
    
    // Détermine si on cherche le plus petit (distance) ou le plus grand (similarité)
    virtual bool isSimilarity() const { return false; }

    std::vector<std::pair<double, int>> getKnn(const Sample& input) const;

public:
    Knn(int k, const Data& train_data) : _k(k), _train_data(train_data) {}
    virtual ~Knn() = default;

    // La prédiction prend juste l'échantillon à tester (les données d'entrainement sont déjà stockées)
    int predict(const Sample& image) const;
    virtual string getName() const { return "Knn Euclide"; }
};

#endif