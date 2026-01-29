#include "ClassificationReport.h"
#include <sstream>
#include <iomanip>
#include <string>

void ClassificationReport::toString() const {
    std::stringstream ss;
    double acc;

    ss << "\n--- Rapport de Classification ---\n";
    // Affichage des compteurs de performance 
    ss << "Succes: " << _ok << " | Echecs: " << _nok << "\n";

    // Calcul de la précision (pourcentage de bonne classification) [cite: 21, 109]
    // Correction : division flottante pour éviter d'obtenir toujours 0.00%
    if (_ok + _nok > 0) { 
        acc = (_ok / (_ok + _nok)) * 100.0; 
    }
    else { acc = 0.0; }

    ss << "Precision: " << std::fixed << std::setprecision(2) << acc << "%\n";
    
    // Affichage de la matrice de confusion 
    ss << "\nMatrice de Confusion (Lignes: Reel, Col: Predit):\n";
    
    // En-tête dynamique basé sur _nbTags
    ss << "    ";
    for(int i = 0; i < _nbTags; i++) ss << std::setw(3) << i;
    ss << "\n    " << std::string(_nbTags * 3, '-') << "\n";

    // Double boucle pour parcourir la matrice de taille _nbTags x _nbTags [cite: 86]
    for(int i = 0 ; i < _nbTags ; i++) {
        ss << i << " |";
        for(int j = 0 ; j < _nbTags ; j++) {
            ss << std::setw(3) << _confusion[i][j];
        }
        ss << "\n";
    }
    
    std::cout << ss.str() << std::endl;
}

void ClassificationReport::add(int real, int predicted) {
    // Sécurité : on vérifie que les étiquettes ne dépassent pas la taille de la matrice
    if (real < 0 || real >= _nbTags || predicted < 0 || predicted >= _nbTags) {
        return; 
    }

    // Incrémentation des compteurs ok/nok 
    if (real == predicted) {
        _ok++;
    } else {
        _nok++;
    }
    
    // Enregistrement dans la matrice de confusion
    _confusion[real][predicted]++;
}
