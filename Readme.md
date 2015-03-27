# cartographie
Le code contenu dans ce dépôt permet une recherche de chemin sur le plateau.

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

