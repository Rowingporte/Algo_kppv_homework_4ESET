#ifndef KNN_H
#define KNN_H

#include "Data.h"
#include <utility>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

class Knn {
protected:
    int _k;
    const Data& _train_data; // REFERENCE vers les données d'apprentissage

    // Méthodes internes
    std::vector<std::pair<double, int>> getKnn(const Sample& input) const;
    int predictSingle(const Sample& input) const;
    
    // Virtuelles pour être modifiées par KnnCosine
    virtual double similarity(const Sample& a, const Sample& b) const;
    virtual bool isSimilarity() const { return false; } // false = distance (plus petit mieux), true = similarité (plus grand mieux)

public:
    // Le constructeur prend les données d'ENTRAINEMENT
    Knn(int k, const Data& train_data);
    virtual ~Knn() = default;

    // La prédiction prend juste l'échantillon à tester (les données d'entrainement sont déjà stockées)
    int predict(const Sample& image) const;
};

#endif