#include "arbre_binaire.h"

//***********noeud et arbre**********
/// Ajoute un noeud_binaire à l'arbre.
/// \param _objet : un pointeur sur l'objet, contenu dans le noeud, que l'on veut ajouter à l'arbre.
/// \param arbre : un pointeur sur l'arbre où l'on va ajouter _objet.
/// \param _copier : fonction générique qui copie un objet dans un autre zone mémoire.
/// \param _compareTo : fonction générique qui compare 2 objets. Renvoie 1 si le 1er est supérieur au 2ème, -1 si le 1er est inférieur au 2èmeet 0 s'il sont égaux.
void ajouter_noeud_dans_arbre(void * _objet, ab arbre, void (* _copier)(void *, void **), int (* _compareTo)(void *, void *)) {
//    nb tmp_noeud;
    nb tmp_arbre = *(arbre->racine);
    nb n = creer_noeud_binaire(_objet, _copier);
    if (tmp_arbre == NULL)
        *(arbre->racine) = n;
    else {
        /*while (tmp_arbre != NULL) {
            tmp_noeud = tmp_arbre;
            if (_compareTo(tmp_arbre->objet, _objet) == -1) {
                tmp_arbre = tmp_arbre->fils_droit;
                if (tmp_arbre == NULL)
                    tmp_noeud->fils_droit = n;
            } else {
                tmp_arbre = tmp_arbre->fils_gauche;
                if (tmp_arbre == NULL)
                    tmp_noeud->fils_gauche = n;
            }
        }*/
        while (_compareTo(tmp_arbre->objet, _objet) != 0) {
            if (_compareTo(tmp_arbre->objet, _objet) == -1) {
                if (tmp_arbre->fils_droit != NULL)
                    tmp_arbre = tmp_arbre->fils_droit;
                else {
                    tmp_arbre->fils_droit = n;
                    tmp_arbre = tmp_arbre->fils_droit;
                }
            } else {
                if (tmp_arbre->fils_gauche != NULL)
                    tmp_arbre = tmp_arbre->fils_gauche;
                else {
                    tmp_arbre->fils_gauche = n;
                    tmp_arbre = tmp_arbre->fils_gauche;
                }
            }
        }
    }
}

/// Supprime un noeud_binaire d' un arbre.
/// \param _objet : un pointeur sur l'objet, contenu dans le noeud, que l'on veut supprimer à l'arbre.
/// \param arbre : un pointeur sur l'arbre où l'on va supprimer _objet.
/// \param _detruire : fonction générique qui supprime un objet de la mémoire.
/// \param _compareTo : fonction générique qui compare 2 objets. Renvoie 1 si le 1er est supérieur au 2ème, -1 si le 1er est inférieur au 2èmeet 0 s'il sont égaux.
/// \param _copier : fonction générique qui copie un objet dans un autre zone mémoire.
void supprimer_noeud_dans_arbre(void * _objet, ab arbre, void (* _detruire)(void **), int (* _compareTo)(void *, void *), void (* _copier)(void *, void **)) {
    nb tmp_arbre = *arbre->racine;
    if (tmp_arbre != NULL) {
        // Recherche du noeud à supprimer
        while (_compareTo(_objet, tmp_arbre->objet) != 0) {
            if(_compareTo(_objet, tmp_arbre->objet) == 1)
                tmp_arbre = tmp_arbre->fils_droit;
            else
                tmp_arbre = tmp_arbre->fils_gauche;
        }
        // Si les 2 fils ou juste le fils droit du noeud à supprimer sont != NULL
        if ((tmp_arbre->fils_gauche != NULL && tmp_arbre->fils_droit != NULL) || (tmp_arbre->fils_droit != NULL)) {
            // Recherche du plus petit noeud de la branche doite du noeud à supprimer.
            nb pere_min = tmp_arbre->fils_droit;
            nb min = pere_min;
            if (pere_min->fils_gauche != NULL)
                min = min->fils_gauche;
            while (min->fils_gauche != NULL) {
                min = pere_min->fils_gauche;
                pere_min = pere_min->fils_gauche;
            }
            if (min->fils_droit != NULL) {
                pere_min->fils_gauche = min->fils_droit;
            }
            _detruire(&tmp_arbre->objet);
            _copier(min->objet, &(tmp_arbre->objet));
            _detruire(&min->objet);
            free(min);
            min = NULL;
        }
        else if (tmp_arbre->fils_gauche != NULL && tmp_arbre->fils_droit == NULL) {
            nb pere_max = tmp_arbre->fils_gauche;
            nb max = pere_max;
            if (pere_max->fils_droit != NULL)
                max = max->fils_droit;
            while (max->fils_droit != NULL) {
                max = pere_max->fils_droit;
                pere_max = pere_max->fils_droit;
            }
            if (max->fils_gauche != NULL) {
                pere_max->fils_droit = max->fils_droit;
            }
            _detruire(&tmp_arbre->objet);
            _copier(max->objet, &(tmp_arbre->objet));
            _detruire(&max->objet);
            free(max);
            max = NULL;
        }
    }
}

/// Supprime tout les noeud de l'arbre.
/// \param n : un pointeur sur le noeud à partir duquel on va le supprimer ainsi que tout ses fils.
/// \param _detruire : fonction générique qui supprime un objet de la mémoire.
void supprimer_tout_dans_arbre(nb * n, void (* _detruire)(void **)) {
    if ((*n) != NULL) {
        if ((*n)->fils_gauche != NULL)
            supprimer_tout_dans_arbre(&(*n)->fils_gauche, _detruire);
        if ((*n)->fils_droit != NULL)
            supprimer_tout_dans_arbre(&(*n)->fils_droit, _detruire);
        _detruire(&(*n)->objet);
        free(*n);
        *n = NULL;
    }
}

/// Recherche un objet dans un arbre.
/// \param _objet : un pointeur sur l'objet, contenu dans le noeud, que l'on veut rechercher à l'arbre.
/// \param arbre : un pointeur sur l'arbre où l'on va rechercher _objet.
/// \param _compareTo : fonction générique qui compare 2 objets. Renvoie 1 si le 1er est supérieur au 2ème, -1 si le 1er est inférieur au 2èmeet 0 s'il sont égaux.
/// \return un pointeur d'un noeud contenant l'objet.
nb rechercher_noeud_dans_arbre(void * _objet, ab arbre,  int (* _compareTo)(void *, void *)) {
    nb n = *arbre->racine;
    while(n != NULL) {
        if(_compareTo(_objet, n->objet) == 0)
            return n;
        if(_compareTo(_objet, n->objet) == 1)
            n = n->fils_droit;
        else
            n = n->fils_gauche;
    }
    return NULL;
}


//********arbre************
/// Crée un arbre_binaire vide.
/// \return un pointeur sur un arbre binaire vide.
ab creer_arbre_binaire(void) {
    ab arbre = (ab) malloc(sizeof(struct arbre_binaire));
    arbre->racine = (nb *) malloc(sizeof(nb));
    *arbre->racine = NULL;
    return arbre;
}

/// Affiche l'arbre.
/// \param arbre : un pointeur sur l'arbre où l'on va ajouter _objet.
/// \param _afficher : fonction générique qui affiche un objet.
void afficher_tout_dans_arbre(ab arbre, void (* _afficher)(void *)) {
    if (arbre == NULL)
        puts("arbre null");
    else {
        if (*arbre->racine == NULL)
            puts("racine == null");
        else {
            nb n = *arbre->racine;
            if (n == NULL)
                puts("n == null");
            else
                afficher_tout(n, _afficher);
        }
    }
}

///
/// \param arbre : un pointeur sur l'arbre que l'on veut supprimer.
/// \param _detruire : fonction générique qui supprime un objet de la mémoire.
void supprimer_arbre(ab * arbre, void (* _detruire)(void **)) {
    supprimer_tout_dans_arbre((*arbre)->racine, _detruire);
    free((*arbre)->racine);
    free(*arbre);
    *arbre = NULL;
}

/// Vérifie si l'arbre est complet à partir du noeud n.
/// \param n : un pointeur sur un noeud qui sert de racine à un arbre.
/// \return 1 si l'arbre est complet, et 0 sinon.
int noeud_binaire_complet(nb n) {
    if (n == NULL)
        return 0;
    if(n->fils_gauche == NULL && n->fils_droit == NULL)
        return 1;
    if((n->fils_droit != NULL && n->fils_gauche == NULL) || (n->fils_droit == NULL && n->fils_gauche != NULL))
        return 0;
    return noeud_binaire_complet(n->fils_gauche) && noeud_binaire_complet(n->fils_droit);
}

/// Vérifie si l'arbre est complet.
/// \param arbre : un pointeur sur l'arbre à vérifier.
/// \return 1 si l'arbre est complet, et 0 sinon.
int arbre_complet(ab arbre) {
    return noeud_binaire_complet(*arbre->racine);
}

/// Donne le nombre de feuille d'un arbre à partir d'un noeud n.
/// \param n : un pointeur sur un noeud qui sert de racine à un arbre.
/// \return un entier représentant le nombre de feuille.
int nb_feuille(nb n) {
    if (n == NULL)
        return 0;
    if (n->fils_gauche == NULL && n->fils_droit == NULL)
        return 1;
    if (n->fils_gauche != NULL && n->fils_droit != NULL)
        return nb_feuille(n->fils_gauche) + nb_feuille(n->fils_droit);
    else if (n->fils_droit != NULL)///////////////////a partir de la ne sert a rien a partir de la si l'arbre est complet
        return nb_feuille(n->fils_droit);
    else if (n->fils_gauche != NULL)
        return nb_feuille(n->fils_gauche);
    else
        return 0;
}

/// Donne le nombre de feuille d'un arbre.
/// \param arbre : un pointeur sur l'arbre.
/// \return un entier représentant le nombre de feuille.
int nombre_feuille(ab arbre) {
    return nb_feuille(*arbre->racine);
}

