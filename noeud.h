#ifndef PROJET_NOEUD_H
#define PROJET_NOEUD_H

#include <stdlib.h>
#include <stdio.h>

struct noeud_binaire {
    void * objet;
    struct noeud_binaire * fils_gauche;
    struct noeud_binaire * fils_droit;
} noeud_binaire;

typedef struct noeud_binaire * nb;


nb creer_noeud_binaire(void *, void (* _copier)(void *, void **));

void supprimer_noeud_binaire(nb *, void (* _detruire)(void **));

void afficher_noeud_binaire(nb, void (* _afficher)(void *));

void afficher_tout(nb, void (* _afficher)(void *));

#endif
