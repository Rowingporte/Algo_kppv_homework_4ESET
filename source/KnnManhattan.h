#ifndef KNNMANHATTAN_H
#define KNNMANHATTAN_H

#include "Knn.h"
#include <cmath>


class KnnManhattan : public Knn {
public:
    // Constructeur : on passe k et train_data à la classe mère Knn
    KnnManhattan(int k, const Data& train_data);

    // On redéfinit la méthode similarity pour Manhattan
    double similarity(const Sample& a, const Sample& b) const override;

    // Pour Manhattan, on trie par distance (plus c'est petit, plus c'est proche)
    // On peut utiliser getKnn de la classe mère si elle trie par ordre croissant.
    virtual ~KnnManhattan() = default;
    virtual string getName() const override { return "Knn Manhattan"; }
};

#endif