#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Sample.h"

using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::cerr;

class Data {
    vector<Sample> _data;
    int _nb_samples;
    int _nb_features;       // Nombre de features par sample
public:
    Data() = default;
    void load(const string& file_name);                 // Charge le fichier texte
    void aspire_les_donnees(std::ifstream& file);       // Recupere les samples et les features du fichier
    void add(int tag, const vector<double>& features);  // Ajoute les samples à la base de donnees
    void toString() const;                              // Affiche la base de donnees
    int nbSamples() const { return _nb_samples; }       // Nombre de samples dans la base de donnees
    Sample& operator[](int index);                      // Acces aux samples par index (ecriture)
    const Sample& operator[](int index) const;          // Idem en const (lecture)
    Data Scale(double factor) const;                    // Creation d'une nouvelle base de donnees normalisee
};

#endif