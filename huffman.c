#include "huffman.h"
#include "arbre_binaire.h"
#include <string.h>

/// Fonction générique appliquée à une struct huffman.
/// Fait une copie d'un huffman.
/// \param _objet : un pointeur de l'huffman à copier
/// \param ptr : un pointeur de pointeur de l'huffman où _objet va être copié
void _copier(void * _objet, void ** ptr) {
    huff * h = (huff *) ptr;
    *h = (huff) malloc(sizeof(struct huffman));
    (*h)->caractere = (char *) calloc(1, sizeof(char));
    (*h)->frequence = (int *) malloc(sizeof(int));
    huff huf = (huff) _objet;
    memcpy((*h)->caractere, huf->caractere, sizeof(char));
    memcpy((*h)->frequence, huf->frequence, sizeof(int));
}

/// Fonction générique appliquée à une struct huffman.
/// Libère l'espace mémoire d'un huffman.
/// \param _objet : un pointeur de pointeur de l'huffman dont on libère la mémoire.
void _detruire(void ** _objet) {
    huff * h = (huff *) _objet;
    free((*h)->caractere);
    (*h)->caractere = NULL;
    free((*h)->frequence);
    (*h)->frequence = NULL;
    free(*_objet);
    *_objet = NULL;
}

/// Fonction générique appliquée à une struct huffman.
/// Affiche un huffman.
/// \param _objet : un pointeur de l'huffman que l'on veut afficher.
void _afficher(void * _objet) {
    huff h = (huff) _objet;
    printf("caractère = %c, frequence = %d\n", *h->caractere, *h->frequence);
}

/// Fonction générique appliquée à une struct huffman.
/// Compare 2 huffman.
/// \param _objet_test : un pointeur du 1er huffman que l'on veut comparer.
/// \param _objet_ref : un pointeur du 2ème huffman que l'on veut comparer.
/// \return 1 si le 1er est supérieur au 2ème.
/// \return -1 si le 1er est inférieur au 2ème.
/// \return 0 si il sont égaux.
int _compareTo(void * _objet_test, void * _objet_ref) {
    huff test = (huff) _objet_test;
    huff ref = (huff) _objet_ref;
    char * c_test = test->caractere;
    char * c_ref = ref->caractere;
    int * f_test = test->frequence;
    int * f_ref = ref->frequence;

    if ((*f_test) < (*f_ref))
        return -1;
    else if ((*f_test) > (*f_ref))
        return 1;
    else {
        if (c_ref != NULL && c_test != NULL) {
            if ((*c_test) < (*c_ref))
                return -1;
            else if ((*c_test) > (*c_ref))
                return 1;
            return 0;
        }
        return 1;
    }
}

/// Fonction générique appliquée à une struct huffman.
/// Crée un huffman résultant de l'addition de 2 autres huffman.
/// \param objet1 : un pointeur du 1er huffman de l'addtion.
/// \param objet2 : un pointeur du 2ème huffman de l'addtion.
/// \return un pointeur de l'huffman résultant de l'addition de objet1 et de objet2.
void * _addition(void *objet1, void *objet2) {
    huff o1 = (huff) objet1;
    huff o2 = (huff) objet2;
    int * frequence = (int*) malloc(sizeof(int));
    *frequence = *o1->frequence + *o2->frequence;
    huff h = creer_huffman("", frequence);
    return h;
}


/// Crée un pointeur d'un huffman avec un caractère et une frequence.
/// \param caractere : une chaine de caractère contenant un seul caractere.
/// \param frequence : un pointeur d'entier représentant la fréquence du caractere dans un texte.
/// \return un pointeur d'huffman
huff creer_huffman(char * caractere, int * frequence) {
    huff h = (huff) malloc(sizeof(struct huffman));
    h->caractere = caractere;
    h->frequence = frequence;
    return h;
}

/// Supprime un huffman de la mémoire.
/// \param h : un pointeur de l'huffman à supprimer.
/// \param _detruire : fonction générique, appliquée à une struct huffman, qui le supprime de la mémoire.
void supprimer_huffman(huff * h, void (* _detruire)(void **)) {
    _detruire((void **) h);
}

/// Affiche un huffman, sous la forme caractere = ..., frequence = ... .
/// \param h : un pointeur de l'huffman que l'on veut afficher.
/// \param _afficher : fonction générique, appliquée à une struct huffman, qui l'affiche.
void afficher_huffman(huff h, void (* _afficher)(void *)) {
    _afficher(h);
}

///
/// \param texte
/// \param taille
/// \param _compareTo
/// \return
ab * creer_liste_min(char * texte, int * taille, int (* _compareTo)(void *, void *)) {
    char * tmp_text = (char *) calloc(strlen(texte) + 1, sizeof(char));
    tmp_text = strcpy(tmp_text, texte);
    int * frequence;
    char caractere[2];
    huff h;
    nb n;
    ab * liste = (ab *) malloc(strlen(texte) * sizeof(ab));
    *taille = 0;
    while (strlen(tmp_text) > 0) {
        frequence = frequence_caractere(tmp_text[0], tmp_text);
        caractere[0] = tmp_text[0];
        h = creer_huffman(caractere, frequence);
        n = creer_noeud_binaire(h, _copier);
        liste[*taille] = creer_arbre_binaire();
        if (*taille == 0) {
            *liste[0]->racine = n;
        } else {
            int i = 0;
            if (_compareTo(h, (*liste[i]->racine)->objet) <= 0) {
                for (int j = *taille; j >= 1; --j) {
                    if (*liste[j]->racine == NULL) {
                        *liste[j]->racine = creer_noeud_binaire((*liste[j - 1]->racine)->objet, _copier);
                    } else {
                        _copier((*liste[j - 1]->racine)->objet, &((*liste[j]->racine)->objet));
                    }
                }
                *liste[0]->racine = n;
            } else {
                while (i < *taille && _compareTo(h, (*liste[i]->racine)->objet) > 0) {
                    ++i;
                }
                if (i == *taille) {
                    *liste[*taille]->racine = n;
                } else {
                    for (int j = *taille; j > i; --j) {
                        if (*liste[j]->racine == NULL) {
                            *liste[j]->racine = creer_noeud_binaire((*liste[j - 1]->racine)->objet, _copier);
                        } else {
                            _copier((*liste[j - 1]->racine)->objet, &((*liste[j]->racine)->objet));
                        }
                    }
                    *liste[i]->racine = n;
                }
            }
        }
        (*taille)++;

        int nb_occ = *frequence;
        int i = 0;
        while (nb_occ > 0) {
            if (tmp_text[i] == caractere[0]) {
                strcpy(&tmp_text[i], &tmp_text[i + 1]);
                nb_occ--;
            } else
                i++;
        }
    }
    liste = (ab *) realloc(liste, (*taille) * sizeof(ab));
    int acc = 0;
    for (int k = 0; k < *taille; ++k) {
        acc += *((huff )(*liste[k]->racine)->objet)->frequence;
    }
    return liste;
}

///
/// \param texte
/// \param _copier
/// \param _compareTo
/// \return
ab fusion(char * texte, void (* _copier)(void *, void **), int (* _compareTo)(void *, void *)) {
    if (texte != NULL) {
        int * taille = (int *) malloc(sizeof(int));
        *taille = 0;
        ab * liste = creer_liste_min(texte, taille, _compareTo);
        ab fusion;
        huff h;
        while (*taille >= 2) {
            h = _addition((*liste[0]->racine)->objet, (*liste[1]->racine)->objet);
            fusion = creer_arbre_binaire();
            (*fusion->racine) = creer_noeud_binaire(h, _copier);
            (*fusion->racine)->fils_gauche = *liste[0]->racine;
            (*fusion->racine)->fils_droit = *liste[1]->racine;
            for (int i = 0; i < *taille - 1; ++i) {
                liste[i] = liste [i + 1];
            }
            (*taille)--;
            liste = (ab *) realloc(liste, *taille * sizeof(ab));
            if (_compareTo((*fusion->racine)->objet, (*liste[0]->racine)->objet) <= 0) {
                liste[0] = fusion;
            } else {
                int i = 0;
                while (i < *taille && _compareTo((*fusion->racine)->objet, (*liste[i]->racine)->objet) > 0) {
                    ++i;
                }
                --i;
                for (int j = 0; j < i; ++j) {
                    liste[j] = liste[j + 1];
                }
                liste[i] = fusion;
            }
        }
        return liste[0];
    }
    return NULL;
}


/// Calcul le nombre d'occurence (frequence) d'un caractère dans un texte.
/// \param c : le caractère dont on recherche la frequence.
/// \param texte : le texte où l'on recherche la frequence du caractère c.
/// \return l'entier représentant la frequence du caractère c dans le texte.
int * frequence_caractere(char c, char * texte) {
    int * f = (int *) calloc(1, sizeof(int));
    *f = 0;
    for (int i = 0; i < (int) strlen(texte); i++) {
        if (texte[i] == c)
            (*f)++;
    }
    return f;
}

/// Code de l'huffman contenu dans un noeud d'un arbre binaire qui est composé de 0 et de 1.
/// Si le noeud est un fils_droit du noeud père alors on ajoute 0 au code et 1 si le noeud est un fils_gauche.
/// Et ainsi de suite jusqu'à la racine en remontant les branches de l'arbre.
/// \param h : un pointeur de l'huffman dont on recherche le code dans l'arbre.
/// \param n : un pointeur du noeud qui représente la racine d'un arbre_bianire.
/// \param _compareTo : fonction générique, appliquée à une struct huffman, qui compare 2 huffman.
/// \return une chaine de caractère, composé de 0 et de 1, représentant le code de h à partir de n.
char * code_noeud(huff h, nb n, int (* _compareTo)(void *, void *)) {
    if (n == NULL) {
        puts("null");
        return "n";
    }
    if(n->fils_gauche != NULL && n->fils_droit != NULL) {
        if (n->fils_gauche->fils_gauche != NULL && n->fils_gauche->fils_droit != NULL) {
            char * tmp = (char *) calloc((size_t) nb_feuille(n) + 1, sizeof(char));
            strcpy(tmp, code_noeud(h, n->fils_gauche, _compareTo));
            if (strlen(tmp) > 0) {
                char * code = (char *) calloc(strlen(tmp) + 2, sizeof(char));
                strcpy(code, "1");
                strcat(code, tmp);
                return code;
            }
        }
        if (_compareTo(h, n->fils_gauche->objet) == 0) {
            return "1";
        }
        if (n->fils_droit->fils_gauche != NULL && n->fils_droit->fils_droit != NULL) {
            char * tmp = (char *) calloc((size_t) nb_feuille(n) + 1, sizeof(char));
            strcpy(tmp, code_noeud(h, n->fils_droit, _compareTo));
            if (strlen(tmp) > 0) {
                char * code = (char *) calloc(strlen(tmp) + 2, sizeof(char));
                strcpy(code, "0");
                strcat(code, tmp);
                return code;
            }
        }
        if (_compareTo(h, n->fils_droit->objet) == 0) {
            return "0";
        }
        return "";
    } else {
        return "f";
    }

}

/// Code de l'huffman contenu dans un noeud d'un arbre binaire qui est composé de 0 et de 1.
/// Si le noeud est un fils_droit du noeud père alors on ajoute 0 au code et 1 si le noeud est un fils_gauche.
/// Et ainsi de suite jusqu'à la racine en remontant les branches de l'arbre.
/// \param h : un pointeur de l'huffman dont on recherche le code dans l'arbre.
/// \param arbre : un pointeur de l'arbre_binaire.
/// \param _compareTo : fonction générique, appliquée à une struct huffman, qui compare 2 huffman.
/// \return une chaine de caractère, composé de 0 et de 1, représentant le code de h dans arbre.
char * code_noeud_dans_arbre(huff h, ab arbre, int (* _compareTo)(void *, void *)) {
    nb n = *arbre->racine;
    char * code = code_noeud(h, n,  _compareTo);
    return code;
}



/// Compresse un texte en un code binaire, selon l'algorithme de Huffman.
/// \param texte : une chaine de caractère que l'on veut compresser.
/// \param arbre : un pointeur sur un arbre binaire correspondant à l'arbre de fusion du texte.
/// \param _compareTo : fonction générique, appliquée à une struct huffman, qui compare 2 huffman.
/// \return une chaine de caractère, composé de 0 et de 1, représentant le code du texte.
char * compression(char * texte, ab arbre, int (* _compareTo)(void *, void *)) {
    if (texte != NULL && strlen(texte) >= 2) {
        char * compresser = (char *) calloc(nombre_feuille(arbre) * strlen(texte) + 1, sizeof(char));
        char c[2];
        for (int i = 0; i < (int) strlen(texte); i++) {
            c[0] = texte[i];
            huff h = creer_huffman(c, frequence_caractere(texte[i], texte));
            char * code = code_noeud_dans_arbre(h, arbre, _compareTo);
            strcat(compresser, code);
            free(h);
        }
        compresser = (char *) realloc(compresser, strlen(compresser) + 1);
        return compresser;
    }
    return NULL;
}

/// Compresse, à partir d'un fichier, un texte en un code binaire, selon l'algorithme de Huffman.
/// \param fichier : un pointeur sur un fichier contenant une chaine de caractère que l'on veut compresser.
/// \param arbre : un pointeur sur un arbre binaire correspondant à l'arbre de fusion du texte.
/// \param _compareTo : fonction générique, appliquée à une struct huffman, qui compare 2 huffman.
/// \return un pointeur sur un fichier contenant une chaine de caractère, composé de 0 et de 1, représentant le code du texte.
FILE * compressionFichier(FILE * fichier, ab arbre, int (* _compareTo)(void *, void *)) {
    int k = 0;
    int t = 2;
    char * texte = (char *) calloc((size_t) t, sizeof(char));
    if (fichier != NULL)
    {
        while(feof(fichier) == 0 ){
            fscanf(fichier, "%c", &(texte[k]));
            k++;
            t++;
            texte = (char *) realloc(texte, (size_t) t * sizeof(char));
        }
        fclose(fichier);
    }
//    printf("texte = %s, taille du texte = %d\n", texte, (int) strlen(texte));
    arbre = fusion(texte, _copier, _compareTo);

    if (texte != NULL && strlen(texte) >= 2) {
        char * compresser = (char *) calloc(nombre_feuille(arbre) * strlen(texte) + 1, sizeof(char));
        char * code;
        huff h;
        char c[2];
        for (int i = 0; i < (int) strlen(texte); i++) {
            c[0] = texte[i];
            h = creer_huffman(c, frequence_caractere(texte[i], texte));
            code = code_noeud_dans_arbre(h, arbre, _compareTo);
            strcat(compresser, code);
        }
        compresser = (char *) realloc(compresser, strlen(compresser) + 1);
        FILE * fichier2;
        fichier2 = fopen("C:\\Users\\Bonjour\\Documents\\Cours\\L3\\Prog_Imp\\Projet\\code.txt", "w+");
        for (int b = 0; b < strlen(compresser) + 1; b++) {
//            printf("comp %c\n", compresser[b]);
            fprintf(fichier2,"%c", compresser[b]);
        }
        fclose(fichier2);
        return fichier2;
    }
    return NULL;
}


/// Décompresse un code binaire en un texte, selon l'algorithme de Huffman.
/// \param code : une chaine de caractère composées de 0 et de 1.
/// \param arbre : un pointeur sur un arbre binaire correspondant à l'arbre de fusion du texte.
/// \return une chaine de caractère correspondant à un texte.
char * decompression(char * code, ab arbre) {
    nb n = *arbre->racine;
    if (code != NULL && n != NULL) {
        char *texte = (char *) calloc((size_t) strlen(code) + 1, sizeof(char));
        int i = 0;
        int j = 0;
        while (i < (int) strlen(code)) {
            while (j < (int) strlen(code) && n->fils_gauche != NULL && n->fils_droit != NULL) {
                if (code[j] == '0')
                    n = n->fils_droit;
                else if (code[j] == '1')
                    n = n->fils_gauche;
                j++;
            }
            strcat(texte, ((huff) n->objet)->caractere);
            i = j;
            n = *arbre->racine;
        }
        texte = (char *) realloc(texte, strlen(texte) + 1);
        return texte;
    }
    return NULL;
}

/// Décompresse un texte en un code binaire, selon l'algorithme de Huffman.
/// \param fichier : un pointeur sur un fichier contenant une chaine de caractère composées de 0 et 1.
/// \param arbre : un pointeur sur un arbre binaire correspondant à l'arbre de fusion du texte.
/// \return
char * decompressionFichier(FILE * fichier, ab arbre) {
    int k = 0;
    int t = 2;
    char * code = (char *) calloc((size_t) t, sizeof(char));;
    if (fichier != NULL)
    {
        while (feof(fichier) == 0 ) {
            fscanf(fichier, "%c", &(code[k]));
//            printf("%c\n", code[k]);
            if (isalpha(code[k])/*code[k] != '1' && code[k] != '0'*/) {
                printf("fichier erroné, k = %d\n", k);
                break;
            }
            k++;
            t++;
            code = (char *) realloc(code, (size_t) t * sizeof(char));
        }
        fclose(fichier);
    }
    printf("code = %s, taille du code = %d\n", code, (int) strlen(code));

    nb n = *arbre->racine;
    if (code != NULL && n != NULL) {
        char * texte = (char *) calloc((size_t) strlen(code) + 1,sizeof(char));
        int i = 0;
        int j = 0;
        while (i < (int) strlen(code)) {
            while (j < (int) strlen(code) && n->fils_gauche != NULL && n->fils_droit != NULL) {
                if (code[j] == '0')
                    n = n->fils_droit;
                else if (code[j] == '1')
                    n = n->fils_gauche;
                j++;
            }
            strcat(texte, ((huff) n->objet)->caractere);
            i = j;
            n = *arbre->racine;
        }
        texte = (char *) realloc(texte, strlen(texte) + 1);
        FILE* fichier2;
        fichier2 = fopen("resultat.txt","w+");
        for(int b=0; b<strlen(texte) + 1;b++){
            fprintf(fichier2,"%c",texte[b]);
        }
        fclose(fichier2);
        return texte;
    }
    return NULL;
}
