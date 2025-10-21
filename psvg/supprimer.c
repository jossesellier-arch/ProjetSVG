#ifndef SUPPRIMER_C
#define SUPPRIMER_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supprimer.h"

// Structure noeud liste chainée
typedef struct Forme {
    char ligne[256];
    struct Forme *suiv;
} Forme;

//  Charger formes dans une liste chainée
Forme* chargerFormes(const char *nomFichier) {
    FILE *f = fopen(nomFichier, "r");
    if (!f) return NULL;

    Forme *tete = NULL, *queue = NULL;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), f)) {
        Forme *nouveau = malloc(sizeof(Forme));
        if (!nouveau) break;
        strcpy(nouveau->ligne, buffer);
        nouveau->suiv = NULL;

        if (tete == NULL)
            tete = nouveau;
        else
            queue->suiv = nouveau;

        queue = nouveau;
    }
    fclose(f);
    return tete;
}

// Afficher formes
void afficherFormes(Forme *tete) {
    int i = 1;
    for (Forme *courant = tete; courant != NULL; courant = courant->suiv)
        printf("%d. %s", i++, courant->ligne);
}

// Supprimer une forme 
Forme* supprimerFormeListe(Forme *tete, int index) {
    if (index < 1 || tete == NULL) return tete;

    if (index == 1) {
        Forme *tmp = tete;
        tete = tete->suiv;
        free(tmp);
        return tete;
    }

    Forme *courant = tete;
    for (int i = 1; courant->suiv != NULL && i < index - 1; i++)
        courant = courant->suiv;

    if (courant->suiv != NULL) {
        Forme *tmp = courant->suiv;
        courant->suiv = tmp->suiv;
        free(tmp);
    }

    return tete;
}

// Réécrire la liste dans le fichier
void sauvegarderFormes(const char *nomFichier, Forme *tete) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) return;

    for (Forme *courant = tete; courant != NULL; courant = courant->suiv)
        fputs(courant->ligne, f);

    fclose(f);
}

// libérer la mémoire
void libererListe(Forme *tete) {
    while (tete) {
        Forme *tmp = tete;
        tete = tete->suiv;
        free(tmp);
    }
}

// Fonction supprimer de base
void supprimerForme() {
    const char *nomFichier = "formes.txt";
    Forme *tete = chargerFormes(nomFichier);

    if (!tete) {
        printf("Aucune forme enregistrée.\n");
        return;
    }

    printf("\nListe des formes :\n");
    afficherFormes(tete);

    int choix;
    printf("\nNuméro de la forme à supprimer : ");
    scanf("%d", &choix);

    tete = supprimerFormeListe(tete, choix);
    sauvegarderFormes(nomFichier, tete);

    printf("Forme supprimée.\n");
    libererListe(tete);
}

#endif
