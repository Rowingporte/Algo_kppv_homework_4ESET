#include "Data.h"
#include <stdexcept>

// Charge le fichier texte
void Data::load(const string& file_name) {
    std::ifstream file(file_name);
    
    if (!file) {
        cerr << "ERREUR : Impossible d'ouvrir le fichier " << file_name << endl;
        return;
    }

    aspire_les_donnees(file);
    file.close();
}

// Recupere les samples et les features du fichier
void Data::aspire_les_donnees(std::ifstream& file) {
    int temp_nb_samples;
    int tag;
    vector<double> tabFeatures;

    file >> temp_nb_samples >> _nb_features;    // Lit le nombre de samples et de features

    string line;
    string elem_line;
    getline(file, line);    // Saute la ligne vide (nombre de feature deja recupere)

    for(int i = 0 ; i < temp_nb_samples ; i++) {
        if (!getline(file, line) || line.empty()) { break; }
        tabFeatures.clear();
        std::stringstream ss(line);
        ss >> tag;      // Lit la note

        while(ss >> elem_line) {
            size_t pos = elem_line.find(':');

            // Format numero:feature
            if (pos = string::npos) {
                // Recupere la feature apres le ':' & conversion string en double
                tabFeatures.push_back(std::stod(elem_line.substr(pos + 1)));
            }

            // Format espace puis feature
            else {
                tabFeatures.push_back(std::stod(elem_line));  // Recupere la feature
            }
        }
        add(tag, tabFeatures);
    }
}

// Ajoute les samples à la base de donnees
void Data::add(int tag, const vector<double>& features) {
    Sample s(tag, features);
    _data.push_back(s);
    _nb_samples = _data.size();     // Met à jour le nombre de samples
}

// Affiche la base de donnees
void Data::toString() const {
    cout << "Nombre samples: " << _nb_samples << " Nombre de features: " << _nb_features << endl;
    cout << "Base de donnees:" << endl;
    for (const Sample& sample : _data) {
        sample.toString();
    }
}

// Acces aux samples par index (ecriture)
Sample& Data::operator[](int index) {
    if (index < 0 || index >= _nb_samples) { throw std::out_of_range("Index invalide dans Data::operator[]"); }
    return _data[index];
}

// Acces aux samples par index (lecture)
const Sample& Data::operator[](int index) const {
    if (index < 0 || index >= _nb_samples) { throw std::out_of_range("Index invalide dans Data::operator[] (const)"); }
    return _data[index];
}

// Creation d'une nouvelle base de donnees normalisee
Data Data::Scale(double factor) const {
    Data scaledData;
    for (const Sample& s : _data) {
        Sample scaledSample = s.scale(factor);      // Multiplication des samples par le facteur
        scaledData.add(scaledSample.getTag(), scaledSample.getFeatures().getVector());  // Ajout dans la nouvelle base
    }
    return scaledData;
}