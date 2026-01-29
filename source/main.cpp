#include <iostream>
#include <iomanip>
#include "Data.h"
#include "Knn.h"
#include "KnnCosine.h"
#include "Sample.h"
#include "ClassificationReport.h"

using namespace std;

int main() {
    cout << "==========================================" << endl;
    cout << "                  DEBUT                   " << endl;
    cout << "==========================================" << endl;



    int choix = 0;
    int k = 1;
    string nomFichier = "";
    int nbClasses = 10;

    // ETAPE 0 : Choix des Donnees
    cout << "1. Chiffres (digits.svm)" << endl;
    cout << "2. Jeux Video critique (jv-train-small.ssvm)" << endl;
    cout << "3. Jeux Video critique (jv-train.ssvm)" << endl;
    cout << "4. Test (test.ssvm)" << endl;
    cout << "5. Test (train.ssvm)" << endl;
    cout << "Entrez 1 à 5 : ";
    cin >> choix;

    cout << "Entrez le nombre de voisins (k) : ";
    cin >> k;

    if (k <= 0) {
        cout << "ERREUR : k doit etre superieur a 0." << endl;
        return 1;
    }

    if (choix == 1) {
        nomFichier = "../../donnees/Digits/digits.svm";
        nbClasses = 10;
    } else if (choix == 2) {
        nomFichier = "../../donnees/jeux_video-critiques/jv-train-small.ssvm";
        nbClasses = 3;
    } else if (choix == 3) {
        nomFichier = "../../donnees/jeux_video-critiques/jv-train.ssvm";
        nbClasses = 3;
    } else if (choix == 4) {
        nomFichier = "../../donnees/Test/test.svm";
        nbClasses = 3;
    } else if (choix == 5) {
        nomFichier = "../../donnees/Test/train.svm";
        nbClasses = 3;
    } else {
        cout << "ERROR : Choix invalide, fermeture." << endl;
        return 1;
    }

    // ETAPE 1 : Chargement des Donnees
    cout << "\n[ETAPE 1] Chargement du fichier..." << endl;
    
    Data data;
    cout << "Chargement du fichier " << nomFichier << endl;
    data.load(nomFichier); 
    
    data.toString(); // Si ça affiche 0 échantillon c'est que le fichier pas été trouvé

    if (data.nbSamples() == 0) {
        cout << "ERREUR : Fichier vide ou introuvable." << endl;
        return 1;
    }

/*


    cout << "==========================================" << endl;
    // ETAPE 2 : Test d'acces a un Sample
    cout << "\n[ETAPE 2] Test d'acces a un Sample..." << endl;
    
    // On prend l'image numero 10 pour voir si elle est bien lue
    try {
        Sample& testSample = data[10];
        testSample.toString();
        cout << "Valeur du pixel 0 : " << testSample[0] << endl; // Verification que la surcharge []
    } catch (const exception& e) {
        cout << "Erreur d'acces : " << e.what() << endl;
    }




    cout << "==========================================" << endl;
    // ETAPE 3 : Test Algo KNN
    cout << "\n[ETAPE 3] Test Algorithme KNN (Distance Euclidienne)..." << endl;
    
    Knn algoEuclide(k, data); // k = 3
    
    // On prend la DERNIERE image du dataset pour tester la prediction
    // (Note : On teste sur une image que l'algo connait déjà, c'est juste pour vérifier que ça ne plante pas)
    int indexTest = data.nbSamples() - 1; 
    Sample& imageTest = data[indexTest];

    cout << "Tentative de prediction sur l'image numero " << indexTest << " (Vrai chiffre : " << imageTest.getTag() << ")" << endl;

    int prediction = algoEuclide.predict(imageTest);

    cout << "Resultat Algo : " << prediction << endl;
    if (prediction == imageTest.getTag()) {
        cout << "--> SUCCES : L'algo a trouve juste" << endl;
    } else {
        cout << "--> SUCCES : L'algo a trouve un chiffre différent de la réalité" << endl;
    }




    cout << "==========================================" << endl;
    // ETAPE 4 : Test Algo KNN Cosine
    cout << "\n[ETAPE 4] Test Algorithme KNN Cosine..." << endl;
    
    KnnCosine algoCosine(k, data); // k = 3
    
    cout << "Tentative de prediction avec Cosinus..." << endl;
    int predictionCos = algoCosine.predict(imageTest);
    
    cout << "Resultat Cosinus : " << predictionCos << endl;

    if (predictionCos == imageTest.getTag()) {
        cout << "--> SUCCES : L'algo a trouve juste" << endl;
    } else {
        cout << "--> ECHEC : L'algo a trouve un chiffre different de la realite" << endl;
    }



    cout << "==========================================" << endl;
    // ETAPE 5 : Rapport
    cout << "\n[ETAPE 5] Sur quel algorithme faire le rapport final ? (1: Euclide, 2: Cosinus) :" << endl;
    
    int choixRapport = 1;
    cin >> choixRapport;

    ClassificationReport report(nbClasses);
    cout << "Calcul du rapport sur toute la base..." << endl;

    for (int i = 0; i < data.nbSamples(); i++) {
        int pred = (choixRapport == 1) ? algoEuclide.predict(data[i]) : algoCosine.predict(data[i]);
        report.add(data[i].getTag(), pred);
        if (i % 200 == 0) cout << "." << flush;
    }

    report.toString(); // Affiche la précision et la matrice de confusion



    cout << "==========================================" << endl;
    // ETAPE 6 : Test de performance pour plusieurs k
    cout << "\n[ETAPE 6] Recherche du meilleur k (on commence a k=2)..." << endl;
    
    int kMax = 2;
    cout << "Entrez la valeur maximale de k a tester : ";
    cin >> kMax;

    int bestK = -1;
    double bestScore = -1.0;

    cout << "\nAnalyse en cours..." << endl;
    cout << " k  | Precision" << endl;
    cout << "----------------" << endl;

    // On commence a k=2 car a k=1, l'algorithme se trouve lui-meme (distance 0)
    for (int currentK = 2; currentK <= kMax; currentK++) {
        ClassificationReport tempReport(nbClasses);
        
        // On relance l'algorithme choisi (Euclide ou Cosinus)
        if (choixRapport == 1) {
            Knn algoTemp(currentK, data);
            for (int i = 0; i < data.nbSamples(); i++) {
                tempReport.add(data[i].getTag(), algoTemp.predict(data[i]));
            }
        } else {
            KnnCosine algoTemp(currentK, data);
            for (int i = 0; i < data.nbSamples(); i++) {
                tempReport.add(data[i].getTag(), algoTemp.predict(data[i]));
            }
        }

        // Calcul du score actuel (version sans setprecision)
        double total = tempReport.getOk() + tempReport.getNok();
        double score = (total > 0) ? (tempReport.getOk() / total) * 100.0 : 0.0;
        
        cout << " " << currentK << "  | " << score << "%" << endl;

        // Mise a jour du meilleur k
        if (score > bestScore) {
            bestScore = score;
            bestK = currentK;
        }
    }

    // --- AFFICHAGE DU VAINQUEUR ---
    cout << "----------------" << endl;
    if (bestK != -1) {
        cout << "RESULTAT : Le meilleur k est " << bestK 
             << " avec une precision de " << bestScore << "%" << endl;
    } else {
        cout << "Aucun test n'a pu etre effectue (kMax doit etre >= 2)." << endl;
    }
    cout << "==========================================" << endl;



    cout << "\n==========================================" << endl;
    cout << "                   FIN                    " << endl;
    cout << "==========================================" << endl;
*/
    return 0;
}