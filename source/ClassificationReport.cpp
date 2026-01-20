#include "ClassificationReport.h"

void ClassificationReport::toString() const {
    std::stringstream ss;
    double acc;

    ss << "\n--- Rapport de Classification ---\n";
    ss << "Succes: " << _ok << " | Echecs: " << _nok << "\n";

    if (_ok + _nok > 0) { acc = _ok / (_ok + _nok) * 100; }
    else { acc = 0; }

    ss << "Precision: " << std::fixed << std::setprecision(2) << acc << "%\n";
    ss << "\nMatrice de Confusion (Lignes: Réel, Col: Prédit):\n";
    ss << "    0  1  2  3  4  5  6  7  8  9\n";
    ss << "    ---------------------------\n";
    for(int i = 0 ; i < 10 ; i++) {
        ss << i << " |";
        for(int j = 0 ; j < 10 ; j++) {
            ss << std::setw(3) << _confusion[i][j];
        }
        ss << "\n";
    }
    cout << ss.str() << endl;
    return;
};