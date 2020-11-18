#include "noeud.h"

/// Crée un noeud.
/// \param _objet : un pointeur sur un objet qui sera contenu dasn le noeud.
/// \param _copier : fonction générique qui copie un objet dans un autre zone mémoire.
/// \return un pointeur sur le noeud créé.
nb creer_noeud_binaire(void * _objet, void (* _copier)(void *, void **)) {
    nb n = (nb) malloc(sizeof(struct noeud_binaire));
    _copier(_objet, &(n->objet));
    n->fils_gauche = NULL;
    n->fils_droit = NULL;
    return n;
}

/// Supprime un noeud de la mémoire.
/// \param n : un pointeur sur le noeud à supprimer.
/// \param _detruire : fonction générique qui supprime un objet de la mémoire.
void supprimer_noeud_binaire(nb * n, void (* _detruire)(void **)) {
    _detruire(&(*n)->objet);
    (*n)->fils_droit = NULL;
    (*n)->fils_gauche = NULL;
    free(*n);
    *n = NULL;
}

/// Affiche un noeud.
/// \param n : un pointeur sur le noeud à afficher.
/// \param _afficher : fonction générique qui affiche un objet.
void afficher_noeud_binaire(nb n, void (* _afficher)(void *)) {
    _afficher(n->objet);
}

/// Affiche un noeud et tout ses fils.
/// \param n : un pointeur sur le noeud racine à afficher.
/// \param _afficher : fonction générique qui affiche un objet.
void afficher_tout(nb n, void (* _afficher)(void *)) {
    if (n == NULL)
        return;
    if(n->fils_gauche != NULL)
        afficher_tout(n->fils_gauche, _afficher);
    _afficher(n->objet);
    if(n->fils_droit != NULL)
        afficher_tout(n->fils_droit, _afficher);
}

