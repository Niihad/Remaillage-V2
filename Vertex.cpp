#include "Vertex.h"

Vertex::Vertex(){}
Vertex::Vertex(float a, float b, float c): x(a), y(b), z(c){}

float Vertex::operator[](int i) const{
    if (i<0 || i>4){
		cerr << "ERREUR: Depacement indice" << endl;
	}
    switch(i){
        case 0: return x; break;
        case 1: return y; break;
        case 2: return z; break;
    }
    return 0;
}

