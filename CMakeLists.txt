cmake_minimum_required(VERSION 3.9)
project(Projet C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet main.c arbre_binaire.c arbre_binaire.h huffman.c huffman.h noeud.c noeud.h)