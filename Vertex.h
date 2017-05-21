#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class Vertex
{
    public:
        Vertex();
        ~Vertex() {}
        Vertex(float x, float y, float z);
        float x, y, z;
        float operator[](int i) const;

};

#endif // VERTEX_H
