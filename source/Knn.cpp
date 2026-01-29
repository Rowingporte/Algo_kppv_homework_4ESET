#include "Knn.h"
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

// Constructeur : on initialise la référence _train_data
Knn::Knn(int k, const Data& train_data) : _k(k), _train_data(train_data) {
}

// Distance Euclidienne classique
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

int Knn::predictSingle(const Sample& input) const {
    auto neighbors = getKnn(input);
    
    // Vote majoritaire
    map<int, int> votes;
    for (const auto& p : neighbors) {
        votes[p.second]++;
    }

    int bestTag = -1;
    int maxVotes = -1;
    for (const auto& v : votes) {
        if (v.second > maxVotes) {
            maxVotes = v.second;
            bestTag = v.first;
        }
    }
    return bestTag;
}

int Knn::predict(const Sample& image) const {
    return predictSingle(image);
}