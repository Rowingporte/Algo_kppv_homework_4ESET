#include "Data.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void Data::load(const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << " [!] ERREUR : Impossible d'ouvrir " << file_name << endl;
        return;
    }
    cout << " [+] Fichier ouvert : " << file_name << endl;
    aspire_les_donnees(file);
    file.close();
}

void Data::aspire_les_donnees(ifstream& file) {
    int nb_prevus, dim_prevue;
    if (!(file >> nb_prevus >> dim_prevue)) return;

    _nb_features = dim_prevue;
    cout << " [i] Lecture de " << nb_prevus << " exemples en dimension " << dim_prevue << "..." << endl;

    for (int i = 0; i < nb_prevus; i++) {
        int tag;
        if (!(file >> tag)) break;

        vector<double> feats(_nb_features, 0.0);
        for (int j = 0; j < _nb_features; j++) {
            string s;
            if (!(file >> s)) break;

            size_t pos = s.find(':');
            if (pos != string::npos) {
                // Format JV (index:valeur)
                int index = stoi(s.substr(0, pos));
                double val = stod(s.substr(pos + 1));
                if (index > 0 && index <= _nb_features) feats[index-1] = val;
                
                // Stop si fin de ligne pour les formats creux (sparse)
                if (file.peek() == '\n' || file.peek() == '\r') break;
            } else {
                // Format Chiffres (valeurs simples)
                feats[j] = stod(s);
            }
        }
        add(tag, feats);

        // Debug : voir la progression
        if ((i + 1) % 1000 == 0) cout << "  > " << (i + 1) << " chargés..." << endl;
    }
    cout << " [OK] Chargement fini : " << _nb_samples << " points en mémoire." << endl;
}

void Data::add(int tag, const vector<double>& features) {
    _data.push_back(Sample(tag, features));
    _nb_samples = (int)_data.size(); 
}

void Data::toString() const {
    cout << "--- Aperçu des données ---" << endl;
    int limit = (_nb_samples < 3) ? _nb_samples : 3;
    for(int i = 0; i < limit; i++) {
        cout << " [" << i << "] ";
        _data[i].toString();
    }
}

Sample& Data::operator[](int index) {
    if (index < 0 || index >= _nb_samples) throw out_of_range("Index out");
    return _data[index];
}

const Sample& Data::operator[](int index) const {
    if (index < 0 || index >= _nb_samples) throw out_of_range("Index out");
    return _data[index];
}