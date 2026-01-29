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

void Knn::Comparaison(int k, const Data& train_data, const Data& test_data, int nbTags) {
    // 1. On crée les objets algos
    Knn knn_euclidean(k, train_data);
    KnnCosine knn_cosine(k, train_data);

    // 2. On crée les rapports (en passant le nombre de classes/tags)
    ClassificationReport report_euclidean(nbTags);
    ClassificationReport report_cosine(nbTags);

    // 3. ON REMPLACE LE .test() PAR UNE BOUCLE
    std::cout << "Calculs en cours..." << std::endl;
    for (int i = 0; i < test_data.nbSamples(); i++) {
        const Sample& s = test_data[i];

        // Pour Euclide
        int predEuclide = knn_euclidean.predict(s);
        report_euclidean.compare(s.getTag(), predEuclide);

        // Pour Cosine
        int predCosine = knn_cosine.predict(s);
        report_cosine.compare(s.getTag(), predCosine);
    }

    // 4. On affiche les résultats (Option A : toString gère le cout)
    std::cout << "\nTest méthode Euclidienne KNN :" << std::endl;
    report_euclidean.toString();

    std::cout << "\nTest méthode Cosine KNN :" << std::endl;
    report_cosine.toString();

    double ScoreEuclidean = report_euclidean.getOk() / (report_euclidean.getOk() + report_euclidean.getNok());
    double ScoreCosine = report_cosine.getOk() / (report_cosine.getOk() + report_cosine.getNok());

    std::cout << "\n=== Comparaison ===" << std::endl;
    std::cout << "SCore KNN Euclidien : " << ScoreEuclidean * 100 << "%" << std::endl;
    std::cout << "SCore KNN Cosine: " << ScoreCosine * 100 << "%" << std::endl;

    if (ScoreCosine > ScoreEuclidean) {
        std::cout << "RESULTAT : l'algorithme Cosine est plus performant pour k = " << k << std::endl;
    } else if (ScoreCosine < ScoreEuclidean) {
        std::cout << "RESULTAT : l'algorithme Euclidien est plus performant pour k = " << k << std::endl;
    } else {
        std::cout << "RESULTAT : Les deux algorithmes ont la même performance pour k = " << k <<std::endl;
    }
}

