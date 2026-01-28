#ifndef CLASSIFICATIONREPORT_H
#define CLASSIFICATIONREPORT_H

#include <vector>
#include <iostream>

class ClassificationReport {
    std::vector<std::vector<int>> _confusion;
    double _ok;
    double _nok;
    int _nbTags; // nombre de classes (10 pour les chiffres, 3 pour JV)

public:
    // Constructeur
    ClassificationReport(int nbTags) : _nbTags(nbTags), _ok(0), _nok(0) { 
        _confusion.resize(_nbTags, std::vector<int>(_nbTags, 0)); 
    }
    
    void toString() const;
    void add(int real, int predicted);

    // Getters
    double getOk() const { return _ok; }
    double getNok() const { return _nok; }
};

#endif