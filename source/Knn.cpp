#include "Knn.h"
#include "KnnCosine.h"           // <--- Pour KnnCosine
#include "KnnManhattan.h"        // <--- Pour KnnManhattan
#include "ClassificationReport.h" // <--- Pour ClassificationReport
#include <iostream>              // <--- Pour std::cout

using namespace std;

// Création d'un classifieur KNN qui prend en paramètre combien de voisins on veut (k) et les données d'entrainement (train_data)
Knn::Knn(int k, const Data& train_data) : _k(k), _train_data(train_data) {
}

// Calcul de la distance Euclidienne entre deux samples
double Knn::similarity(const Sample& a, const Sample& b) const {
    double somme = 0.0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        double diff = a[i] - b[i];
        somme += diff * diff;
    }
    return std::sqrt(somme);
}

// Récupération des K voisins dans la base d'ENTRAINEMENT
vector<pair<double, int>> Knn::getKnn(const Sample& input) const {
    vector<pair<double, int>> distances;

    // On compare l'input (Test) avec chaque image de l'apprentissage (_train_data)
    for (int i = 0; i < _train_data.nbSamples(); i++) {
        const Sample& trainSample = _train_data[i];
        double val = this->similarity(input, trainSample);
        distances.push_back(make_pair(val, trainSample.getTag()));
    }

    // Tri (Croissant pour distance, Décroissant pour similarité)
    if (this->isSimilarity()) {
        std::sort(distances.begin(), distances.end(), [](const pair<double, int>& a, const pair<double, int>& b) {
            return a.first > b.first; 
        });
    } else {
        std::sort(distances.begin(), distances.end(), [](const pair<double, int>& a, const pair<double, int>& b) {
            return a.first < b.first;
        });
    }

    // On garde les k premiers
    if (distances.size() > (size_t)_k) {
        distances.resize(_k);
    }
    return distances;
}

/* Appel de la prédiction pour un seul sample 
en le comparant aux k plus proches voisins 
puis ajout dans une map pour le vote majoritaire, 
vote fait en retournant l'étiquette la plus fréquente */

int Knn::predictSingle(const Sample& input) const {
    auto neighbors = getKnn(input); // Récupère les {distance, tag}
    
    // On utilise double pour stocker des poids (pas des entiers)
    map<int, double> weightedVotes;

    for (const auto& p : neighbors) {
        double dist = p.first;
        int tag = p.second;

        // Éviter la division par zéro si l'objet est exactement le même
        double weight = 1.0 / (dist + 0.0001); 
        
        weightedVotes[tag] += weight; // On ajoute le poids au lieu de +1
    }

    int bestTag = -1;
    double maxWeight = -1.0;

    for (const auto& v : weightedVotes) {
        if (v.second > maxWeight) {
            maxWeight = v.second;
            bestTag = v.first;
        }
    }
    return bestTag;
}

int Knn::predict(const Sample& image) const {
    return predictSingle(image);
}


