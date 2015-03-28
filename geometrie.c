#include <math.h>
#include "geometrie.h"


float distance(coord pointA, coord pointB) {
    int u=(pointA.x-pointB.x),
        v=(pointA.y-pointB.y);
    return (float)sqrtf((float)u*u+v*v);
}

float distance_heuristique(coord a, coord b) {
    // TODO ajouter un coeff si nécessaire
    return 10*distance(a, b);
}

int collisionSegmentSegment(coord A, coord B, coord I, coord P){
    coord D,E;
    D.x = B.x - A.x;
    D.y = B.y - A.y;
    E.x = P.x - I.x;
    E.y = P.y - I.y;
    double denom = D.x*E.y - D.y*E.x;
    if (denom==0)
        return 0;   // Segment et droite parallèles
    float t = - (A.x*E.y-I.x*E.y-E.x*A.y+E.x*I.y) / denom;
    if (t<0 || t>1)
        return 0;
    float u = - (-D.x*A.y+D.x*I.y+D.y*A.x-D.y*I.x) / denom;
    if (u<0 || u>1)
        return 0;
    return 1;
}

int collisionDroiteCercle(coord A, coord B, coord C, float rayon) {
    coord u;
    u.x = B.x - A.x;
    u.y = B.y - A.y;
    coord AC;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    float numerateur = u.x*AC.y - u.y*AC.x;   // norme du vecteur v
    if (numerateur <0)
        numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.
    float denominateur = sqrt(u.x*u.x + u.y*u.y);  // norme de u
    float CI = numerateur / denominateur;

    return CI<rayon;
}
int collisionPointCercle(coord A, coord C, float rayon) {
    return distance(A, C) <= rayon;
}
int collisionSegmentCercle(coord A, coord B, coord C, float rayon){
    if (!collisionDroiteCercle(A, B, C, rayon))
        return 0;  // si on ne touche pas la droite, on ne touchera jamais le segment
    coord AB, AC, BC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    BC.x = C.x - B.x;
    BC.y = C.y - B.y;

    float pscal1 = AB.x*AC.x + AB.y*AC.y;  // produit scalaire
    float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;  // produit scalaire
    if (pscal1>=0 && pscal2>=0)
        return 1;   // I entre A et B, ok.
    // dernière possibilité, A ou B dans le cercle
    if (collisionPointCercle(A, C, rayon))
        return 1;
    if (collisionPointCercle(B, C, rayon))
        return 1;
    return 0;
}
