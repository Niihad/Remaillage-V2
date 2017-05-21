#include<iostream>
#include <stdio.h>  // printf
#include <stdbool.h>
#include <Build.h>

#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char* argv[]) {
	argv[1] = "obj/knot.off";
    FILE *source = fopen(argv[1], "r");
    Build build;
    int *info = build.info_off(source);
    Vertex *verteces = build.init_vertex(source, info[0]);
    int **faces = build.init_faces(source,verteces, info[1]);
    vector<int> tmp;
    int del = 0;
    //build.save_off(faces,verteces, info, 0, 1, 1);


    string filename =  "obj/list4.txt";
    ifstream file(filename.c_str(), ifstream::in);
    if(file){
        string ligne;
        istringstream iss;
        int x,y,z;
        while (getline(file, ligne, '\n')){
            istringstream iss(ligne.c_str());
			/* la ligne correspond a un sommet */
            iss >> x >> y >> z;
            tmp = build.verif(faces, x, y, info[1]);
            if(tmp.size()==2){
                del += build.deletFace(faces, x, y, info[1]);
            }else{
                tmp = build.verif(faces, y, z, info[1]);
                if(tmp.size()==2){
                    del += build.deletFace(faces, y, z, info[1]);
                }else{
                    tmp = build.verif(faces, z, x, info[1]);
                    if(tmp.size()==2){
                        del += build.deletFace(faces, z, x, info[1]);
                    }
                }
            }

        }
    }else{
        cerr << "ERREUR : Lecture impossible du fichier !" << endl;
    }


    build.save_off(faces,verteces, info, del);

    /*for(int i=0; i<500; i++){
        if(faces[i] != NULL){
            tmp = build.verif(faces, faces[i][0], faces[i][1], info[1]);
            if(tmp.size()==2){
                del ++;
                build.save_off(faces,verteces, info, faces[i][0], faces[i][1], del);
            }else{
                tmp = build.verif(faces, faces[i][1], faces[i][2], info[1]);
                if(tmp.size()==2){
                    del ++;
                    build.save_off(faces,verteces, info, faces[i][0], faces[i][1], del);
                }else{
                    tmp = build.verif(faces, faces[i][2], faces[i][0], info[1]);
                    if(tmp.size()==2){
                        del ++;
                        build.save_off(faces,verteces, info, faces[i][0], faces[i][1], del);
                    }
                }
            }
        }
    }*/


   // print_faces(faces, info[1]);
    fclose(source);
	return 0;
}
