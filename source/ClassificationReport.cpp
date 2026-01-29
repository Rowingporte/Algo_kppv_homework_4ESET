#include "ClassificationReport.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

void ClassificationReport::toString() const {
    std::stringstream ss;
    double acc = 0.0;

    ss << "\n--- Rapport de Classification ---\n";
    ss << "Succes: " << _ok << " | Echecs: " << _nok << "\n";

    double total = _ok + _nok;
    if (total > 0) { 
        acc = (static_cast<double>(_ok) / total) * 100.0; 
    }

    ss << "Precision: " << std::fixed << std::setprecision(2) << acc << "%\n";
    
    ss << "\nMatrice de Confusion (Lignes: Reel, Col: Predit):\n";
    
    // En-tête
    ss << "    ";
    for(int i = 0; i < _nbTags; i++) ss << std::setw(4) << i;
    ss << "\n    " << std::string(_nbTags * 4 + 2, '-') << "\n";

    // Corps de la matrice
    for(int i = 0 ; i < _nbTags ; i++) {
        // Aligne l'indice de ligne sur 2 caractères pour garder les barres verticales droites
        ss << std::setw(2) << i << " |"; 
        for(int j = 0 ; j < _nbTags ; j++) {
            ss << std::setw(4) << _confusion[i][j];
        }
        ss << "\n";
    }
    
    std::cout << ss.str() << std::endl;
}

void ClassificationReport::add(int real, int predicted) {
    if (real < 0 || real >= _nbTags || predicted < 0 || predicted >= _nbTags) {
        return; 
    }

    if (real == predicted) {
        _ok++;
    } else {
        _nok++;
    }
    
    _confusion[real][predicted]++;
}