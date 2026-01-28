#ifndef KNN_H
#define KNN_H

#include "Data.h"
#include <vector>
#include <utility>

class Knn {
protected:
    int _k;                    // Nombre de voisins à considérer
    const Data& _lazy_train;   // La référence vers la base de données (Nommé _lazy_train sur l'UML)
    
    // Trouve les K plus proches voisins : retourne liste de <Distance, Étiquette>
    std::vector<std::pair<double, int>> getKnn(const Sample& input) const;

    // Fait la prédiction pour uhn seul sample
    int predictSingle(const Sample& input) const;

    // Calcule la distance euclidienne entre deux images (virtual pour KnnCosine)
    virtual double similarity(const Sample& a, const Sample& b) const;

    // Pour le tri (false dans knn, true dans knnCosine)
    virtual bool isSimilarity() const { return false; } 

public:
    // Constructeur
    Knn(int k, const Data& data);

    // Destructeur (virtual pour KnnCosine)
    virtual ~Knn() = default;

    // Devine étiquette (chiffre) de l'image
    int predict(const Sample& image) const;
};

#endif