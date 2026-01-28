#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Sample.h"

using std::string;
using std::vector;

class Data {
private:
    vector<Sample> _data;
    int _nb_samples;
    int _nb_features; // Nombre de caractéristiques par Sample (dimension)

public:
    // Constructeur par défaut : Initialise compteurs à 0
    Data() = default;
    
    // Ouverture fichier
    void load(const string& file_name);

    // Méthode interne (helper) qui lit le flux du fichier ligne par ligne
    // C'est elle qui fait le "parsing" du format spécifique du fichier
    void aspire_les_donnees(std::ifstream& file);

    // Ajoute un nouveau  exemple manuellement dans la liste _data
    // Crée l'objet Sample correspondant
    void add(int tag, const vector<double>& features);

    // Affiche le contenu de la base de données dans la console
    void toString() const;

    // Getter : Renvoie simplement le nombre d'images chargées
    int nbSamples() const { return _nb_samples; }

    // Surcharge [] : Permet d'accéder à l'image numéro i
    Sample& operator[](int index);

    // Surcharge [] : Lecture Seule (pour les objets const)
    const Sample& operator[](int index) const;
    
    // Crée nouvelle base de données (Data) où toutes les valeurs sont multipliées 
    Data Scale(double factor) const;
};

#endif