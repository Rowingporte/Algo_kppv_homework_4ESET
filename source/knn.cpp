#include "knn.h"

// A refaire

virtual vector<Sample> Knn::predict(Data* test_data) {
    vector<Sample> result;
    for (int i = 0; i < test_data->nbSamples(); ++i) {
        result.push_back(predictSingle(test_data[i]));
    }
    return result;
}

vector<pair<double, int>> Knn::getKnn(const Sample& sample) {
    vector<pair<double, int>> distances;
    for (int i = 0; i < _lazy_train->nbSamples(); ++i) {
        const Sample& trainSample = _lazy_train->getSample(i);
        double dist = similarity(sample, trainSample);
        distances.push_back({dist, trainSample.get_tag()});
    }

    sort(distances.begin(), distances.end());

    if (distances.size() > (size_t)_k) { distances.resize(_k); }
    return distances;
}

virtual void Knn::predictSingle(const Sample& sample) {
    int bestTag = -1;
    int maxVotes = 0;
    vector<pair<double,int>> neighbors = getKnn(sample);
    map<int, int> voteCounter;
    for (const auto& neighbor : neighbors) {
        VoteCounter[neighbor.second]++;
    }
    for (const auto& vote : voteCounter) {
        if (vote.second > maxVotes) {
            maxVotes = vote.second;
            bestTag = vote.first;
        }
    }
    sample.setPredictedTag(bestTag);
}   

virtual double Knn::similarity(Sample a, Sample b) {
    double sum = 0;
    for(int i = 0 ; i < a.size() ; i++) { sum += (a[i] - b[i]) * (a[i] - b[i]); }
    return sqrt(sum);
}

