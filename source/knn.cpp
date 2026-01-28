#include "Knn.h"
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// Constructeur
Knn::Knn(int k, const Data& data) : _k(k), _lazy_train(data) {
}

// Calcul de Distance Euclidienne (Racine carrée de la somme des différences au carré)
double Knn::similarity(const Sample& a, const Sample& b) const {
    double somme = 0.0;
    size_t n = a.size(); // On suppose que a et b ont la même dimension
    
    for (size_t i = 0; i < n; i++) {
        double diff = a[i] - b[i];
        somme += diff * diff;
    }
    return std::sqrt(somme);
}

// Recherche des k voisins
std::vector<pair<double, int>> Knn::getKnn(const Sample& input) const {
    vector<pair<double, int>> distances;

    // On parcourt toutes les images d'entrainement
    for (int i = 0; i < _lazy_train.nbSamples(); i++) {
        
        const Sample& trainSample = _lazy_train[i]; // référence constante vers l'image
        
        double val = this->similarity(input, trainSample); // Calcule score de similarité
        
        distances.push_back(make_pair(val, trainSample.getTag())); // On stocke le duo (Score, Tag)
    }

    // On trie la liste
    if (this->isSimilarity()) {
        // MODE SIMILARITÉ : +grand = mieux donc tri décroissant
        std::sort(distances.begin(), distances.end(), 
            [](const pair<double, int>& a, const pair<double, int>& b) {
                return a.first > b.first; 
            });
    } else {
        // MODE DISTANCE : +petit = mieux donc tri Croissant
        std::sort(distances.begin(), distances.end(),
            [](const pair<double, int>& a, const pair<double, int>& b) {
                return a.first < b.first;
            });
    }

    // On garde que les k premiers éléments
    if (distances.size() > (size_t)_k) {
        distances.resize(_k);
    }

    return distances;
}

// Prédiction
int Knn::predictSingle(const Sample& input) const {
    auto neighbors = getKnn(input); // Récupérer les voisins

    // Compter les votes (Map : chiffre -> nombre de votes)
    map<int, int> votes;
    for (const auto& paire : neighbors) {
        int candidat = paire.second; // paire.second est le tag
        votes[candidat]++;
    }

    // Trouver le vainqueur
    int bestCandidat = -1;
    int maxVotes = -1;

    for (const auto& element : votes) {
        if (element.second > maxVotes) {
            maxVotes = element.second;
            bestCandidat = element.first;
        }
    }
    return bestCandidat;
}

// Méthode publique
int Knn::predict(const Sample& image) const {
    return predictSingle(image);
}