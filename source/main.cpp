#include <iostream>
#include <iomanip>
#include <string>
#include "Data.h"
#include "Knn.h"
#include "KnnEuclidean.h"
#include "KnnCosine.h"
#include "KnnManhattan.h"
#include "Sample.h"
#include "ClassificationReport.h"

using namespace std;

int main() {
    string fichierTrain = "";
    string fichierTest = "";
    int choix = 0;
    int k = 0;
    int nbNote = 0;

    while(choix != 1 && choix != 2) {
    cout << "===== CHOIX DU TYPE DE DONNEES =====" << endl; // "DU" et non "TU"
    cout << "1 : Chiffres " << endl;
    cout << "2 : Jeux-videos" << endl;
    cin >> choix;
    if (choix != 1 && choix != 2) {
        cout << "Choix inconnu, veuillez recommencer." << endl;
    }
}
    
    if(choix == 1){
        fichierTrain = "donnees/Test/train.svm";
        fichierTest = "donnees/Test/test.svm";
        nbNote = 10;
    }

    if(choix == 2){
        fichierTrain = "donnees/Test/JV/train.ssvm";
        fichierTest = "donnees/Test/JV/test.ssvm"; 
        nbNote = 3;
    }

    cout << "Entrez le nombre de voisins (k) pour le test : ";
    cin >> k;

    // Etape 1 : Chargement des deux bases (Train et Test)
    cout << "\n[ETAPE 1] Chargement des fichiers..." << endl;
    
    Data dataTrain;
    Data dataTest;
    cout << "Chargement Train : " << fichierTrain << endl;
    dataTrain.load(fichierTrain);
    cout << "Chargement Test : " << fichierTest << endl;
    dataTest.load(fichierTest);
    
    // Etape 2 : Creation des algorithmes et affichage des resultats
    cout << "\n[ETAPE 2] Creation des algorithmes et affichage des resultats" << endl;

    ClassificationReport report(nbNote);

    KnnEuclidean algoEuclide(k, dataTrain);
    report.affichage_algo(algoEuclide, dataTest);

    KnnCosine algoCosine(k, dataTrain);
    report.affichage_algo(algoCosine, dataTest);

    KnnManhattan algoManhattan(k, dataTrain);
    report.affichage_algo(algoManhattan, dataTest);
    

    return 0;
}

