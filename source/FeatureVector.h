#ifndef FEATUREVECTOR_H
#define FEATUREVECTOR_H

#include <vector>
#include <cmath>
#include <iostream>

class FeatureVector {
    private:
        //double _norme; // Pas utile
        std::vector<double> _vector; // Tableau dynamique qui stocke les valeurs réelles des caractéristiques
    public:
        // Constructeur par défaut
        FeatureVector(int dimension = 0, double val = 0.0);
        
        // Constructeur de conversion (transforme une liste de nombres en objet FeatureVector)
        FeatureVector(std::vector<double> data);

        // Calcule racine carrée de la somme des carrés des éléments
        double norme() const; 

        // Surcharge de l'opérateur de multiplication
        double operator*(const FeatureVector& other) const;
        
        // Surcharge de l'opérateur [] (lecture/écriture)
        double& operator[](int index);
        
        // Surcharge de l'opérateur [] (lecture seule pour les objets const)
        double operator[](int index) const;
        
        // Retourne taille du vecteur
        size_t size() const;
        
        // Retourne le vecteur
        const std::vector<double>& getVector() const;
};

#endif