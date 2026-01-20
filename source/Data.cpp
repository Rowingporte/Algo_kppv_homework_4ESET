#include "Data.h"

void Data::load(const string& file_name) {
    std::ifstream file(file_name);
    if (!file) {
        cerr << "Impossible d'ouvrir le fichier : " << file_name << endl;
        return;
    }
    aspire_les_donnees(file);
    file.close();
}

void Data::aspire_les_donnees(std::ifstream& file) {
    int tag;
    double feature;
    vector<double> tabFeatures;
    string line;

    file >> _nb_samples >> _nb_features;

    for (int i = 0; i < _nb_samples; i++) {
        tabFeatures.clear();
        file >> tag;
        for (int j = 0; j < _nb_features; j++) {
            file >> feature;
            tabFeatures.push_back(feature);
        }
        add(tag, tabFeatures);
    }  
}

void Data::add(int tag, const vector<double>& features) {
    Sample sample(tag, features);
    _data.push_back(sample);
}

void Data::toString() const {
    for (int i = 0 ; i < _nb_samples; i++) {
        cout << "Sample " << i << " :" << endl;
        _data[i].toString();
    }
}

Sample Data::operator[](int index) {
    if (index < 0 || index >= _nb_samples) { throw std::out_of_range("Index hors des limites"); }
    return _data[index];
}

Data Data::Scale(double factor) const {
    Data scaledData;
    for(const Sample& s : _data) {
        Sample scaledSample = s.Scale(s, factor);
        scaledData.add(scaledSample.get_tag(), scaledSample.get_features());
    }
    return scaledData;
}