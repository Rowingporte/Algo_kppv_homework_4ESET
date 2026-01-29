#include "Knn.h"
#include "KnnEuclidean.h"
#include "KnnCosine.h"
#include "KnnManhattan.h"
#include "ClassificationReport.h"
#include <iostream>

using namespace std;

// Calcul de la distance/similitude entre le sample de test et chaque donnée d'entraînement
vector<pair<double, int>> Knn::getKnn(const Sample& input) const {
    vector<pair<double, int>> distances;
    for (int i = 0; i < _train_data.nbSamples(); i++) {
        double val = this->similarity(input, _train_data[i]);
        distances.push_back({val, _train_data[i].getTag()});
    }

    auto comp = [this](const pair<double, int>& a, const pair<double, int>& b) {
        return this->isSimilarity() ? a.first > b.first : a.first < b.first;
    };
    
    sort(distances.begin(), distances.end(), comp);
    if (distances.size() > (size_t)_k) distances.resize(_k);
    return distances;
}

// Récupère les k voisins les plus proches et effectue un vote pondéré pour la prédiction finale
int Knn::predict(const Sample& input) const {
    auto neighbors = getKnn(input);
    map<int, double> weightedVotes;

    for (const auto& p : neighbors) {
        double weight = 1.0 / (p.first + 0.0001);
        weightedVotes[p.second] += weight;
    }

    int bestTag = -1;
    double maxWeight = -1.0;
    for (auto const& [tag, weight] : weightedVotes) {
        if (weight > maxWeight) {
            maxWeight = weight;
            bestTag = tag;
        }
    }
    return bestTag;
}

int Knn::predict(const Sample& image) const {
    return predictSingle(image);
}


