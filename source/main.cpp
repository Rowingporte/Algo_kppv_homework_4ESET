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
    cout << "==========================================" << endl;
    cout << "                  DEBUT                   " << endl;
    cout << "==========================================" << endl;

    int choix = 0;
    int kInitial = 3;
    string fichierTrain = "";
    string fichierTest = "";
    int nbClasses = 10;

    // ETAPE 0 : Choix des Donnees
    cout << "1. Chiffres (Digits)" << endl;
    cout << "2. Jeux Video (JV)" << endl;
    cout << "Entrez 1 ou 2 : ";
    cin >> choix;

    cout << "Entrez le nombre de voisins (k) pour le test initial : ";
    cin >> kInitial;

    if (choix == 1) {
        // Chemins pour les chiffres
        fichierTrain = "donnees/Test/train.svm";
        fichierTest = "donnees/Test/test.svm"; 
        nbClasses = 10;
    } else if (choix == 2) {
        // Chemins pour JV
        fichierTrain = "donnees/Test/JV/train.ssvm";
        fichierTest = "donnees/Test/JV/test.ssvm"; 
        nbClasses = 3;
    } else {
        cout << "ERROR : Choix invalide." << endl;
        return 1;
    }

    // ETAPE 1 : Chargement des deux bases (Train et Test)
    cout << "\n[ETAPE 1] Chargement des fichiers..." << endl;
    
    Data dataTrain;
    cout << "Chargement Train : " << fichierTrain << endl;
    dataTrain.load(fichierTrain);

    Data dataTest;
    cout << "Chargement Test  : " << fichierTest << endl;
    dataTest.load(fichierTest);

    if (dataTrain.nbSamples() == 0 || dataTest.nbSamples() == 0) {
        cout << "ERREUR : Un des fichiers est vide ou introuvable." << endl;
        return 1;
    }

    cout << "Train: " << dataTrain.nbSamples() << " | Test: " << dataTest.nbSamples() << endl;

    // ETAPE 2 : Test d'acces rapide
    cout << "\n[ETAPE 2] Verification rapide..." << endl;
    dataTest[0].toString();

    // ETAPE 3 & 4 : Initialisation des Algos avec la base d'ENTRAINEMENT
    Knn algoEuclide(kInitial, dataTrain);
    KnnCosine algoCosine(kInitial, dataTrain);
    KnnManhattan algoManhattan(kInitial, dataTrain);

    // Test sur le premier exemple du fichier de TEST
    Sample& sampleTest = dataTest[0];
    cout << "\n[TEST] Prediction sur le 1er exemplaire du fichier TEST" << endl;
    cout << "Vrai Tag : " << sampleTest.getTag() << endl;
    cout << "Prediction Euclide : " << algoEuclide.predict(sampleTest) << endl;
    cout << "Prediction Cosine  : " << algoCosine.predict(sampleTest) << endl;
    cout << "Prediction Manhattan : " << algoManhattan.predict(sampleTest) << endl;
    cout << "\n[ETAPE 4] Comparaison des algorithmes KNN sur la base de TEST pour k = " << kInitial << "..." << endl;

    // ETAPE 5 : Rapport de Classification
    cout << "\n==========================================" << endl;
    cout << "Que voulez-vous faire ?" << endl;
    cout << "1. Rapport detaille Euclide" << endl;
    cout << "2. Rapport detaille Cosinus" << endl;
    cout << "3. Rapport detaille Manhattan" << endl;
    cout << "4. COMPARAISON GLOBALE (pour les slides)" << endl;
    cout << "Votre choix : ";
    int choixRapport;
    cin >> choixRapport;

    if (choixRapport == 4) {
        // Appelle ta méthode qui fait défiler tous les algos d'un coup
        algoEuclide.Comparaison(kInitial, dataTrain, dataTest, nbClasses);
    } else {
        ClassificationReport report(nbClasses);
        cout << "Calcul en cours..." << endl;

        for (int i = 0; i < dataTest.nbSamples(); i++) {
            int pred;
            if (choixRapport == 1) pred = algoEuclide.predict(dataTest[i]);
            else if (choixRapport == 2) pred = algoCosine.predict(dataTest[i]);
            else pred = algoManhattan.predict(dataTest[i]);

            report.compare(dataTest[i].getTag(), pred);
            if (i % 100 == 0) cout << "." << flush;
        }
        cout << endl;
        report.toString(); // Affiche la matrice et le % final
    }

  
    cout << "==========================================" << endl;
    cout << "                   FIN                    " << endl;
    cout << "==========================================" << endl;
    return 0;
}