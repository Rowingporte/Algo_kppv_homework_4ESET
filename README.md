cd C:\Perso\INSA_Rennes\Cours\S7\Cpp\Projet\HW_\source mingw32-make MyExecutable.exe

L’objectif est de programmer en C++ de A à Z un classifieur de type kppv (k plus proches voisins). Un classifieur est un outil qui permet d’apprendre, à partir de données, à classer des objets. Dans notre exemple, l’objectif est de reconnaître à partir de caractéristiques extraites d’un tracé sur tablette tactile, le chiffre qui a été écrit par l’utilisateur. Un classifieur est alors en général entraîné avec des données (d’apprentissage) pour lesquels nous connaissons la classe (ici le chiffre de 0 à 9 qui a été dessiné) et il apprend à faire le lien entre ce qu’il observe, les caractéristiques (ici, de type courbure, centre de gravité, points singuliers, etc.) et la classe.

Un kppv est un classifieur qui fait parti de la famille des classifieurs paresseux : il ne produit pas de modèle à partir des données : lorsque on l’interrogesur une nouvelle instance à classer, il la compare (mesure de distance ou de similarité) avec toutes les instances de sa base de référence (base d’apprentissage) et renvoi comme étiquette l’étiquette obtenue par le vote des k plus proches voisins (vote éventuellement pondéré par la distance entre le voisin et l’instance en question).

L’objectif est de développer un classifieur knn en C++ qui fonctionne en ligne de commande. Ce classifieur devra prendre en entrée, au minimum, deux fichiers et le paramètre k :

un fichier contenant les données d’apprentissage (instances de références)
un fichier contenant les données de test, des exemples que l’on veut étiqueter automatiquement et sur lesquelles on veut évaluer la performance de votre classifieur (pourcentage de bonnes étiquettes prédites)
k, le nombre de voisin que l’on fait voter pour la prédiction d’étiquette
Le classifieur devra : — lire et stocker les données en mémoire — faire la prédiction de la classe de chaque exemple de test suivant le principe du knn — produire une sortie (console ou fichier) de l’étiquette prédite accompagné de sa probabilité — produire une évaluation objective du classifieur :

le pourcentage de bonne classification sur la base de test
une matrice de confusion montrant les confusions du classifieurs (la diagonale indique les bonnes réponses)
