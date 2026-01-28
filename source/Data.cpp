#include "Data.h"
#include <stdexcept>

using namespace std;

// Charge le fichier texte
void Data::load(const string& file_name) {
    ifstream file(file_name);
    
    if (!file) {
        cerr << "ERREUR : Impossible d'ouvrir le fichier " << file_name << endl;
        return;
    }

    aspire_les_donnees(file);
    file.close();
}

// En gros transforme données du fichier texte en objets utilisables par le code
void Data::aspire_les_donnees(ifstream& file) {
    int nb_samples_in_file;
    int dimension;
    
    file >> nb_samples_in_file >> dimension;
    _nb_features = dimension;

    for (int i = 0; i < nb_samples_in_file; i++) { // Pour chaque exemple
        int tag;
        file >> tag; // Extrait remier nombre de la ligne 

        // Initialise un vecteur de la bonne taille
        vector<double> features(_nb_features, 0.0); 

        // On lit les caractéristiques une par une
        for (int j = 0; j < _nb_features; j++) {
            string s;
            if (!(file >> s)) break; // Lit l'élément suivant et arrête quand il n'y en a plus

            size_t pos = s.find(':'); // position du caractère :

            if (pos != string::npos) { // Si caractère : n'existe pas dans la chaîne, find() renvoie string::npos
                
                // FORMAT JV
                int index = stoi(s.substr(0, pos)); // Coupe le texte avant le : (stoi : String TO Integer)
                double val = stod(s.substr(pos + 1)); // Coupe le texte après le : (stod : String TO Double)


                if (index > 0 && index <= _nb_features) {
                    features[index-1] = val;
                }
                
                // si un des \n ou \r ou fin de fichier, on arrête
                if (file.peek() == '\n' || file.peek() == '\r' || file.eof()) {
                    break;
                }
            }  
            else {
                // FORMAT CHIFFRES
                features[j] = stod(s); // stod : String TO Double (on converti en double)
            }
        }
        add(tag, features);
    }
}

// Ajoute un Sample et met à jour le compteur
void Data::add(int tag, const vector<double>& features) {
    Sample s(tag, features);

    _data.push_back(s);

    _nb_samples = _data.size(); // Nombre d'échantillon

}

// Affiche toute la data dans la console
void Data::toString() const {
    cout << "Nombre samples : " << _nb_samples << " exemples (Dimension: " << _nb_features << ")" << endl;
    for (const Sample& sample : _data) {
        sample.toString();
    }
}

// Accès à un sample spécifique (Lecture/Écriture)
Sample& Data::operator[](int index) {
    // Vérif si index bien dans la data
    if (index < 0 || index >= _nb_samples) {
        throw out_of_range("Index invalide dans Data::operator[]");
    }
    return _data[index];
}

// Accès à un sample spécifique (Lecture)
const Sample& Data::operator[](int index) const {
    if (index < 0 || index >= _nb_samples) {
        throw out_of_range("Index invalide dans Data::operator[] (const)");
    }
    return _data[index];
}

// Normalisation des données
Data Data::Scale(double factor) const {
    Data scaledData;
    
    scaledData._nb_features = _nb_features; // On récup la dimension

    // On parcourt chaque sample
    for (const Sample& s : _data) {
        Sample scaledSample = s.scale(factor); // On multiplie le sample par le facteur
        
        scaledData.add(scaledSample.getTag(), scaledSample.getFeatures().getVector()); // On l'ajoute à la nouvelle base de données
    }

    return scaledData;
}