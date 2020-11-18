#ifndef PROJET_ARBRE_BINAIRE_H
#define PROJET_ARBRE_BINAIRE_H

#include "noeud.h"
#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

struct arbre_binaire {
    struct noeud_binaire ** racine;
} arbre_binaire;

typedef struct arbre_binaire * ab;

//***********noeud et arbre**********
void ajouter_noeud_dans_arbre(void *, ab, void (* _copier)(void *, void **), int (* _compareTo)(void *, void *));
void supprimer_noeud_dans_arbre(void *, ab, void (* _detruire)(void **), int (* _compareTo)(void *, void *), void (* _copier)(void *, void **));
void supprimer_tout_dans_arbre(nb *, void (* _detruire)(void **));
nb rechercher_noeud_dans_arbre(void *, ab,  int (* _compareTo)(void *, void *));

//***********arbre**********
ab creer_arbre_binaire(void);
//ab initialiser_arbre_binaire(nb *);
void afficher_tout_dans_arbre(ab, void (* _afficher)(void *));
void supprimer_arbre(ab *, void (* _detruire)(void **));
int arbre_complet(ab);
int nb_feuille(nb);
int nombre_feuille(ab);

#endif
