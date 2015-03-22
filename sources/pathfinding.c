



PointList astar(Point* start, Point* goal) {
    // C'est là qu'on va gérer l'ajout d'ennemis.

    set_is_open(start);


    start->gScore = 0;
    start->fScore = distance_heuristique(*start, *goal);


    printf("commence la boucle\n");
    while(!is_open_empty()) {
        Point* current = pop_best_open_point();
        printf("%d\n", current->neighborCount);

        // On a fini, on reconstruit le chemin grâce au parent de chaque point.
        if (current->type == CIBLE)
            return reconstruct_path(goal);

        current->visited = true;

        int i;
        for (i = 0; i < current->neighborCount; ++i) {
            Point* currentNeighbor = current->voisins[i];
            if (currentNeighbor->visited)
                continue;

            int tentative_gScore = current->gScore + distance_directe(*current, *currentNeighbor);

            if(!currentNeighbor->is_open || tentative_gScore < currentNeighbor->gScore) {
                currentNeighbor->parent = current;
                currentNeighbor->gScore = tentative_gScore;
                currentNeighbor->fScore = tentative_gScore + distance_heuristique(*currentNeighbor, *goal);

                if (!currentNeighbor->is_open)
                    set_is_open(currentNeighbor);
            }
        }
    }

    printf("pas de chemin trouvé !\n");
    PointList pointList;
    return pointList;
}

PointList reconstruct_path(Point* goal) {
    PointList inverted_path;
    vector_init(&inverted_path);

    Point* current = goal;

    while (current->type != DEBUT) {
        vector_append(&inverted_path, current);
        current = current->parent;
    }
    vector_append(&inverted_path, current);

    // Maintenant on retourne la liste ! En plus on sait le nombre de points.

    PointList full_path;
    vector_init(&full_path);

    int i;
    for (i = inverted_path.size-1; i >= 0; --i)
        vector_append(&full_path, vector_get(&inverted_path,i));

    return full_path;
}
