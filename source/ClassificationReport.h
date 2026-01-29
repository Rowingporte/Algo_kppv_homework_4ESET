#ifndef CLASSIFICATIONREPORT_H
#define CLASSIFICATIONREPORT_H

#include "Data.h"
#include "Knn.h"
#include "KnnCosine.h"
#include "KnnManhattan.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Knn;
class Data;

class ClassificationReport {
    vector<vector<int>> _confusion;
    double _ok;
    double _nok;
    int _nbTags; 

public:
    ClassificationReport(int nbTags) : _nbTags(nbTags), _ok(0), _nok(0) { _confusion.resize(_nbTags, vector<int>(_nbTags, 0)); }
    void toString() const;                  // Affiche le rapport de classification
    void compare(int real, int predicted);  // Compare les notes reel et predit et met a jour la matrice de confusion
    double getOk() const { return _ok; }    // Nombre de classifications correctes
    double getNok() const { return _nok; }  // Nombre de classifications incorrectes
    void affichage_algo(Knn& algo, Data& dataTest, int nbNote); // Affichage pour un algo donne
};

#endif