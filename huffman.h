#ifndef PROJET_HUFFMAN_H
#define PROJET_HUFFMAN_H

#include "arbre_binaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct huffman {
    char * caractere;
    int * frequence;
} huffman;

typedef struct huffman * huff;

//*************************fonction génériques***********************
void _copier(void *, void **);
void _detruire(void **);
void _afficher(void *);
int _compareTo(void *, void *);
void * _addition(void *, void *);

//************huffman***********************
huff creer_huffman(char *, int *);
void supprimer_huffman(huff *, void (* _detruire)(void **));
void afficher_huffman(huff, void (* _afficher)(void *));

//************fusion***********************
ab * creer_liste_min(char *, int *, int (* _compareTo)(void *, void *));
ab fusion(char * texte, void (* _copier)(void *, void **), int (* _compareTo)(void *, void *));

//************compression/décompression***********************
int * frequence_caractere(char, char *);
//char * code_noeud_dans_arbre(huff, ab,  int (* _compareTo)(void *, void *));
//char * code_noeud(huff, nb,  int (* _compareTo)(void *, void *));
char * compression(char *, ab, int (* _compareTo)(void *, void *));
FILE * compressionFichier(FILE *, ab, int (* _compareTo)(void *, void *));
char * decompression(char *, ab);
char * decompressionFichier(FILE *, ab);



//ab * creer_liste_min(char *, int *);
//ab ab_finale(ab *, int *);

#endif
