

#ifndef MESHSUBSIMP_MESH_HPP
#define MESHSUBSIMP_MESH_HPP

#include "SimpleMesh.h"

class Mesh
{
public:
    typedef std::map< std::pair<unsigned, unsigned>, std::vector<unsigned>> Edge2Faces;
    std::vector<Vertex> verts;
    std::vector<Face> faces;
    Edge2Faces edge2Faces;
    unsigned int glist;

public:
    void Init();
    void Render();

    void Load(const char* fileName);
    void Save(const char* fileName);
    void LoopSubdivisionOneStep();
    void Simplification();

private:
    void ResetComputing();
    void RecomputeEdgeToFaces(Face &, unsigned);
    Vector3D GetNormalTriangle(Face &);
    Vertex *CalculateOddVertex(unsigned, unsigned, std::vector<unsigned> &);
    void CalculateEvenVertex(unsigned);

    void ComputeErrorMetric();
};


#endif //MESHSUBSIMP_MESH_HPP
