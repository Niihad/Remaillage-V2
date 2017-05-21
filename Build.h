#ifndef BUILD_H
#define BUILD_H

#include <stdlib.h> // atof
#include <stdio.h>  // printf
#include <stdbool.h>
#include <algorithm>
#include <Vertex.h>

class Build{
    public:
        Build();
        bool verif_off(FILE *fichier);
        int *info_off(FILE *fichier);
        Vertex *init_vertex(FILE *fichier, int nbVotex);
        int **init_faces(FILE *fichier, Vertex *list_vertex, int nbFace);
        bool doublonFace(vector<int> tmp, int p);
        vector<int> sommetVoisin(int **faces, int p, int nbFace);
        vector<int> verif(int **faces, int p1, int p2, int nbFace);
        void print_faces(int **faces, int nb);
        int deletFace(int **faces, int p1, int p2, int nb);
        void save_off(int **faces, Vertex *verteces, int *info, int val);

};

#endif // BUILD_H
