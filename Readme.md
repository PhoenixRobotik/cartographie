# cartographie
Le code contenu dans ce dépôt permet une recherche de chemin sur le plateau.

## Utilisation
Ceci est une "boite noire" dans le sens où seul pathfinding.h a besoin d'être inclus
dans le reste du projet.
Ici main.c est un exemple de "reste du projet".

 void pathfinding_init();
Cette fonction devrait être appelée au démarrage du robot.
Si elle n'est pas appelée au démarrage, elle l'est à la première recherche de chemin.

 int pathfinding(int start_x, int start_y, int cible_x, int cible_y);
Retourne 0 si pas de chemin trouvé, et sinon 1 (TODO : longueur du chemin)

 int return_length_of_path_found();
Retourne la longueur du chemin

 void return_path_found(int tableau[][2]);
Retourne dans le tableau donné la liste des points de passage.

 int nouvel_obstacle_rond(int x, int y, int rayon);
Ajoute un obstacle temporaire et renvoie le nombre d'obstacles présents ou -1 si erreur.

 void reinitialise_obstacles_temporaires();
Réinitialise les obstacles temporaires créés manuellement avec la méthode ci-dessus.


## Fonctionnement (pas encore complètement fixé)

### Les Obstacles
On définit les obstacles comme 
* des lignes (paires de points)
* des disques (centre et rayon de l'obstacle (souvent = 0))
Le rayon des disques est le réel (on définit le rayon du robot d'autre part).

Les obstacles doivent définir la zone accessible par LE CENTRE du robot (donc on
doit se faire chier avec les marges, oui, mais c'est bon pour la complexité de 
l'algorithme.. En fait c'est le périmètre de la zone rouge.

### Les points
On définit une grille pour "découper" la table. En fait on renseigne uniquement
la taille de la grille et le décallage à l'origine.


### L'algorithme
C'est du A*, donc fonctionnement classique.

