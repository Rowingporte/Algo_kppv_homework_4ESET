#include <iostream>
#include <iomanip>
#include <string>
#include "Data.h"
#include "Knn.h"
#include "KnnCosine.h"
#include "KnnManhattan.h"
#include "Sample.h"
#include "ClassificationReport.h"

using namespace std;

int main() {
    int choix = 0;
    int kInitial = 3;
    int nbNote = 10;

    string fichierTrain = "../../donnees/Test/train.svm";
    string fichierTest = "../../donnees/Test/test.svm";
    nbNote = 10;

    /*fichierTrain = "../../donnees/Test/JV/train.ssvm";
    fichierTest = "../../donnees/Test/JV/test.ssvm"; 
    nbNote = 3;*/

    // Etape 1 : Chargement des deux bases (Train et Test)
    cout << "Entrez le nombre de voisins (k) pour le test initial: ";
    cin >> kInitial;

    cout << "\n[ETAPE 1] Chargement des fichiers..." << endl;
    
    Data dataTrain;
    cout << "Chargement Train : " << fichierTrain << endl;
    dataTrain.load(fichierTrain);

    Data dataTest;
    cout << "Chargement Test  : " << fichierTest << endl;
    dataTest.load(fichierTest);

    // Etape 2 : Creation des algorithmes et affichage des resultats

    cout << "\n[ETAPE 2] Creation des algorithmes et affichage des resultats..." << endl;

    ClassificationReport report(nbNote);

    Knn algoEuclide(kInitial, dataTrain);
    report.affichage_algo(algoEuclide, dataTest, nbNote);

    KnnCosine algoCosine(kInitial, dataTrain);
    report.affichage_algo(algoCosine, dataTest, nbNote);

    KnnManhattan algoManhattan(kInitial, dataTrain);
    report.affichage_algo(algoManhattan, dataTest, nbNote);

    return 0;
}

