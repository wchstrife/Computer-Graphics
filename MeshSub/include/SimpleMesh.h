// FILE PROVIDED BY THE COURSE

#ifndef MESHSUBSIMP_SIMPLE_HPP
#define MESHSUBSIMP_SIMPLE_HPP

#include "Geometry.h"
#include <vector>
#include <list>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

class Vertex
{
    public:
        Vector3D pos;
        std::vector<unsigned> adjVerts;
        bool isBoundary;
        unsigned index = 0;

    Vertex &operator=(const Vertex& right)
    {
        for (unsigned i = 0; i < right.adjVerts.size(); ++i) adjVerts.push_back(right.adjVerts[i]);
        pos = right.pos;
        isBoundary = right.isBoundary;
        return *this;
    }
};

class Face
{
    public:
        unsigned verts[3];
        Vertex *oddsVerts[3];

        Face()
        {
            oddsVerts[0] = nullptr;
            oddsVerts[1] = nullptr;
            oddsVerts[2] = nullptr;
        }

        unsigned vertOppositeTo(unsigned v0, unsigned v1)
        {
            assert(verts[0] == v0 || verts[1] == v0 || verts[2] == v0);
            assert(verts[0] == v1 || verts[1] == v1 || verts[2] == v1);

            for (unsigned i = 0; i < 3; ++i)
                if (verts[i] != v0 && verts[i] != v1) return verts[i];
            return -1;
        }
        Face &operator=(const Face& right)
        {
            for (unsigned i = 0; i < 3; ++i) verts[i] = right.verts[i];
            return *this;
        }
};

#endif