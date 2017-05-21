#include "build.h"

/* ****************************************************************** */
/* ************************** Initialisation ************************ */
/* ****************************************************************** */

Build::Build(){
}

/* Verifie que le fichier passé en parametre est conforme */
bool Build::verif_off(FILE *fichier){
	 /* Test si on peut ouvrir l'image */
	if (fichier == NULL){
		fprintf(stderr, "Impossible d'ouvrrir le fichier \n");
		exit(1);
    }
    /* Test si c'est bien un fichier du type .off */
	if(fgetc(fichier) != 'O' || fgetc(fichier) != 'F' || fgetc(fichier) != 'F'){
		fprintf(stderr, "Ce n'est pas un fichier de type .off \n");
		exit(1);
    }
    return true;
}

/* Nombre de sommets, faces, aretes */
int *Build::info_off(FILE *fichier){
    int *info = new int[3];
    if(verif_off(fichier)){
        fscanf(fichier, "%d %d %d", &info[0], &info[1], &info[2]);
        return info;
    }
    return NULL;
}

/* Construit la liste des vertex present dans le fichier OFF */
Vertex *Build::init_vertex(FILE *fichier, int nbVotex){
    Vertex *list_vertex = new Vertex[nbVotex];
    float coord[3] = {0};
    for(int i=0; i<nbVotex; i++){
        fscanf(fichier, "%f %f %f", &coord[0], &coord[1], &coord[2]);
        Vertex vertex(coord[0], coord[1], coord[2]) ;
        list_vertex[i] = vertex ;
    }
    return list_vertex;
}

/* Construit la liste des faces present dans le fichier OFF */
int **Build::init_faces(FILE *fichier, Vertex *list_vertex, int nbFace){
    int **list_face = new int*[nbFace];
    for(int i=0; i<nbFace;i++){
        list_face[i] = new int[3];
    }
    int face[4] = {0};
    for(int i=0; i<nbFace; i++){
        fscanf(fichier, "%d %d %d %d", &face[0], &face[1], &face[2],&face[3]);
        for(int j=0; j<3;j++){
            list_face[i][j] = face[j+1];
        }
    }
    return list_face;
}


/* ****************************************************************** */
/* ************************** Test collapse ************************* */
/* ****************************************************************** */


/* retourne true si la valeur est presente dans la liste */
bool Build::doublonFace(vector<int> tmp, int p){
    for(unsigned int i=0; i<tmp.size(); i++){
        if(tmp[i] == p){
            return true;
        }
    }
    return false;
}

/* retourne la liste des sommet voisin du sommet p */
vector<int> Build::sommetVoisin(int **faces, int p, int nbFace){
    /* ajout dans la liste tout les voisin du sommet p */
    vector<int> l_face;
    for(int i=0; i<nbFace; i++){
        if(faces[i] != NULL){
            for(int j=0; j<3;j++){
                if(faces[i][j] == p){
                    l_face.push_back(i);
                }
            }
        }
    }
    vector<int> tmp;
    for(unsigned int i=0; i<l_face.size();i++){
        for(int j=0; j<3; j++){
            if(p != faces[l_face[i]][j] && !doublonFace(tmp,faces[l_face[i]][j])){
                tmp.push_back(faces[l_face[i]][j]);
            }
        }
    }
    sort(tmp.begin(), tmp.end());
    return tmp;
}

/* retourne une liste des sommet en commun entre le sommet p1 et p2 */
vector<int> Build::verif(int **faces, int p1, int p2, int nbFace){
    vector<int> tmp1 = sommetVoisin(faces, p1, nbFace);
    vector<int> tmp2 = sommetVoisin(faces, p2, nbFace);
    vector<int> equal_vertex;
    unsigned int c1 = 0, c2 = 0;
    if(tmp1.size()==0 || tmp2.size()==0){
        return equal_vertex;
    }else{
        while(c1< tmp1.size() && c2<tmp2.size()){
            if(tmp1[c1] == tmp2[c2]){
                equal_vertex.push_back(tmp1[c1]);
                c1++;
                c2++;
            }else if(tmp1[c1] < tmp2[c2]){
                c1++;
            }else{
                c2++;
            }
        }
    }
    return equal_vertex;
}

void Build::print_faces(int **faces, int nb){
    for(int i=0; i<nb; i++){
        if(faces[i] != NULL){
            for(int j=0; j<3;j++){
                cout << faces[i][j] << " ";
            }
            cout << endl;
        }
    }
}


/* ****************************************************************** */
/* ********************* Collapse + construction ******************** */
/* ****************************************************************** */


/* Supprime les faces apres collapse */
int Build::deletFace(int **faces, int p1, int p2, int nb){
    int del = 0;
    for(int i=0; i<nb; i++){
        int cpt = 0;
        if(faces[i] != NULL){
            for(int j=0; j<3;j++){
                if(faces[i][j] == p1 || faces[i][j] == p2){
                    if(faces[i][j] == p1){
                        faces[i][j] = p2;
                    }
                    cpt++;
                }
            }
            if(cpt == 2){
                faces[i] = NULL;
                del++;
            }
        }
    }
    return del;
}

void Build::save_off(int **faces, Vertex *verteces, int *info, int val){
    FILE *fichier = fopen("obj/teste.off", "w");
    fprintf(fichier, "OFF \n");
    fprintf(fichier, "%d %d %d \n",info[0],info[1]-val,(info[1]-val)*3/2);
    for(int i=0; i<info[0]; i++){
        fprintf(fichier,"%f %f %f \n",verteces[i][0],verteces[i][1],verteces[i][2]);
    }
    for(int i=0; i<info[1]; i++){
        if(faces[i] != NULL){
            fprintf(fichier,"3 %d %d %d \n",faces[i][0],faces[i][1],faces[i][2]);
        }
    }
    fclose(fichier);
}


