#include "Knn.h"
#include "KnnEuclidean.h"
#include "KnnCosine.h"
#include "KnnManhattan.h"
#include "ClassificationReport.h"
#include <iostream>

using namespace std;

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

void Knn::Comparaison(int k, const Data& train_data, const Data& test_data, int nbTags) {
    KnnEuclidean knnE(k, train_data);
    KnnCosine knnC(k, train_data);
    KnnManhattan knnM(k, train_data);

    ClassificationReport repE(nbTags), repC(nbTags), repM(nbTags);

    cout << "\n[Running Global Comparison]..." << endl;
    for (int i = 0; i < test_data.nbSamples(); i++) {
        repE.compare(test_data[i].getTag(), knnE.predict(test_data[i]));
        repC.compare(test_data[i].getTag(), knnC.predict(test_data[i]));
        repM.compare(test_data[i].getTag(), knnM.predict(test_data[i]));
        if (i % 100 == 0) cout << "." << flush;
    }

    cout << "\n\n=== RÉSULTATS POUR LES SLIDES ===" << endl;
    cout << "--- EUCLIDE ---" << endl; repE.toString();
    cout << "\n--- COSINE ---" << endl; repC.toString();
    cout << "\n--- MANHATTAN ---" << endl; repM.toString();
}