#include "ClassificationReport.h"

// Affiche le rapport de classification
void ClassificationReport::toString() const {
    std::stringstream ss;
    double precision = 0.0;
    double total = _ok + _nok;

    if (total > 0) { precision = _ok / total * 100; }
    ss << "\n\nRapport de Classification:" << endl;
    ss << "Succes: " << _ok << " et  Echecs: " << _nok << " => Precision: " << precision << endl;
    ss << "\nMatrice de Confusion (Lignes: Reel, Colonnes: Preditiction):\n" << endl;
    
    // Entête du tableau de resultat
    ss << "    ";
    for(int i = 0 ; i < _nbTags ; i++) { ss << std::setw(4) << i; }
    ss << "\n    " << "------------------------------------------" << endl;

    // Tableau de resultat
    for(int i = 0 ; i < _nbTags ; i++) {
        ss << std::setw(2) << i << " |"; 
        for(int j = 0 ; j < _nbTags ; j++) { ss << std::setw(4) << _confusion[i][j]; }
        ss << endl;
    }
    cout << ss.str() << endl;
}

// Compare les notes reel et predit et met a jour la matrice de confusion
void ClassificationReport::compare(int real, int predicted) {
    if (real < 0 || real >= _nbTags || predicted < 0 || predicted >= _nbTags) { return; }   // Verification des valeurs
    if (real == predicted) { _ok++;}    // Prediction correcte
    else { _nok++; }
    _confusion[real][predicted]++;      // Mise a jour de la matrice de confusion
}