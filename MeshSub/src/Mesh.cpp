
#include "Application.hpp"
#include "Mesh.hpp"
#include <algorithm>
#include <glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

static unsigned GetIndex(Face &f, unsigned i)
{
    auto it = std::find(f.verts, f.verts + 3, i);
    if (it != f.verts + 3)
        return std::abs(std::distance(f.verts, it));
    return 42;
}

static unsigned GetPosition(Face &face, unsigned i0, unsigned i1)
{
    unsigned indArr0 = GetIndex(face, i0);
    unsigned indArr1 = GetIndex(face, i1);
    if ((indArr0 == 0 && indArr1 == 1) || (indArr0 == 1 && indArr1 == 0))
        return (2);
    else if ((indArr0 == 0 && indArr1 == 2) || (indArr0 == 2 && indArr1 == 0))
        return (1);
    else
        return (0);
}

static void ApplyFaceVerts(Face &f, unsigned i0, unsigned i1, unsigned i2)
{
    f.verts[0] = i0;
    f.verts[1] = i1;
    f.verts[2] = i2;
}

Vertex *Mesh::CalculateOddVertex(unsigned i0, unsigned i1, std::vector<unsigned> &f)
{
    Vertex *v = new Vertex();
    Vertex &v0 = verts[i0];
    Vertex &v1 = verts[i1];

    if (v0.isBoundary && v1.isBoundary)
    {
        v->pos = (v0.pos + v1.pos) * 0.5f;
        v->isBoundary = true;
        if (f.size() != 1)
            std::cerr << "ERROR" << std::endl;
        faces[f[0]].oddsVerts[GetPosition(faces[f[0]], i0, i1)] = v;
    } else
    {
        if (f.size() != 2)
            std::cerr << "ERROR" << std::endl;
        unsigned i2 = faces[f[0]].vertOppositeTo(i0, i1);
        unsigned i3 = faces[f[1]].vertOppositeTo(i0, i1);
        Vertex &v2 = verts[i2];
        Vertex &v3 = verts[i3];
        v->pos = 3.0 / 8.0 * (v0.pos + v1.pos) + 1.0 / 8.0 * (v2.pos + v3.pos);
        faces[f[0]].oddsVerts[GetPosition(faces[f[0]], i0, i1)] = v;
        faces[f[1]].oddsVerts[GetPosition(faces[f[1]], i0, i1)] = v;
    }
    v->index = verts.size();
    return (v);
}

void Mesh::RecomputeEdgeToFaces(Face &f, unsigned index)
{
    for (unsigned i = 0; i < 3; ++i)
    {
        unsigned v0 = fmin(f.verts[i], f.verts[(i + 1) % 3]);
        unsigned v1 = fmax(f.verts[i], f.verts[(i + 1) % 3]);
        Edge2Faces::iterator iter = edge2Faces.find(std::make_pair(v0, v1));
        if (iter == edge2Faces.end())
        {
            std::vector<unsigned> curFaces;
            curFaces.push_back(index);
            edge2Faces[std::make_pair(v0, v1)] = curFaces;
        } else
            edge2Faces[std::make_pair(v0, v1)].push_back(index);
    }
}

void Mesh::ResetComputing()
{
    edge2Faces.clear();

    for (unsigned i = 0; i < faces.size(); i++)
    {
        Face &f = faces[i];
        verts[f.verts[0]].adjVerts.clear();
        verts[f.verts[1]].adjVerts.clear();
        verts[f.verts[2]].adjVerts.clear();
    }
    for (unsigned i = 0; i < faces.size(); i++)
    {
        Face &f = faces[i];
        verts[f.verts[0]].adjVerts.push_back(f.verts[1]);
        verts[f.verts[0]].adjVerts.push_back(f.verts[2]);
        verts[f.verts[1]].adjVerts.push_back(f.verts[0]);
        verts[f.verts[1]].adjVerts.push_back(f.verts[2]);
        verts[f.verts[2]].adjVerts.push_back(f.verts[0]);
        verts[f.verts[2]].adjVerts.push_back(f.verts[1]);
        for (unsigned j = 0; j < 3; ++j)
            faces[i].oddsVerts[j] = 0;
        RecomputeEdgeToFaces(f, i);
    }
    for (unsigned i = 0; i < verts.size(); ++i)
    {
        std::set<unsigned> rmRedunt;
        for (std::vector<unsigned>::iterator iter = verts[i].adjVerts.begin();
             iter != verts[i].adjVerts.end(); ++iter)
            rmRedunt.insert(*iter);
        verts[i].adjVerts.clear();
        for (std::set<unsigned>::iterator iter = rmRedunt.begin();
             iter != rmRedunt.end(); ++iter)
            verts[i].adjVerts.push_back(*iter);
    }
}

void Mesh::CalculateEvenVertex(unsigned i0)
{
    Vertex *v = &verts[i0];
    Vector3D sum;
    auto n = v->adjVerts.size();
    double beta = (1.0 / n) * ((5.0 / 8.0) - \
                powf((3.0 / 8.0 + 0.25 * cos(2.0 * M_PI / n)), 2.0f));

    for (auto i : v->adjVerts)
        sum += verts[i].pos;
    v->pos = v->pos * (1.0 - n * beta) + sum * beta;
}

void Mesh::LoopSubdivisionOneStep()
{
    unsigned nbFaces = faces.size();
    unsigned nbVerts = verts.size();

    Mesh::ResetComputing();
    for (auto &e : edge2Faces)
    {
        unsigned i0 = e.first.first;
        unsigned i1 = e.first.second;
        verts.emplace_back(*CalculateOddVertex(i0, i1, e.second));
    }
    for (unsigned i = 0; i < nbVerts; i++)
        CalculateEvenVertex(i);
    for (int i = 0; i < nbFaces; i++)
    {
        Face &f = faces[i];
        unsigned i0 = f.verts[0];
        unsigned i1 = f.verts[1];
        unsigned i2 = f.verts[2];
        ApplyFaceVerts(f, f.oddsVerts[2]->index, f.oddsVerts[0]->index, f.oddsVerts[1]->index);
        Face f1;
        ApplyFaceVerts(f1, i0, f.oddsVerts[2]->index, f.oddsVerts[1]->index);
        Face f2;
        ApplyFaceVerts(f2, f.oddsVerts[2]->index, i1, f.oddsVerts[0]->index);
        Face f3;
        ApplyFaceVerts(f3, f.oddsVerts[1]->index, f.oddsVerts[0]->index, i2);
        faces.push_back(f1);
        faces.push_back(f2);
        faces.push_back(f3);
    }
}

void Mesh::ComputeErrorMetric()
{
    std::vector<glm::mat4x4> qs(faces.size());

    for (unsigned i = 0; i < faces.size(); i++)
    {
        return;
    }
}

void Mesh::Simplification()
{
    unsigned nbFaces = faces.size();
    unsigned nbVerts = verts.size();
    std::vector<Vertex> newVerts;
    std::vector<Face> newFaces;

    throw std::logic_error("Mesh simplification not implemented");
}

void Mesh::Load(const char *fileName)
{
    std::ifstream input(fileName);
    std::stringstream sin;
    std::string curLine;
    Vector3D p;
    unsigned v[3];
    unsigned tcoord[3];
    char t;

    while (getline(input, curLine))
    {
        if (curLine.substr(0, 2) == "v ")
        {
            sin.clear();
            sin << curLine;
            sin >> t >> p.x >> p.y >> p.z;
            Vertex v;
            v.pos = p;
            v.isBoundary = false;
            verts.push_back(v);
        } else if (curLine.substr(0, 2) == "f ")
        {
            if (curLine.find("/") != std::string::npos)
                sscanf(curLine.c_str(), "f %d/%d %d/%d %d/%d", &v[0], &tcoord[0], &v[1], &tcoord[1], &v[2], &tcoord[2]);
            else
                sscanf(curLine.c_str(), "f %d %d %d", &v[0], &v[1], &v[2]);

            --v[0];
            --v[1];
            --v[2];
            Face f;
            f.verts[0] = v[0];
            f.verts[1] = v[1];
            f.verts[2] = v[2];
            faces.push_back(f);

            verts[v[0]].adjVerts.push_back(v[1]);
            verts[v[0]].adjVerts.push_back(v[2]);
            verts[v[1]].adjVerts.push_back(v[0]);
            verts[v[1]].adjVerts.push_back(v[2]);
            verts[v[2]].adjVerts.push_back(v[0]);
            verts[v[2]].adjVerts.push_back(v[1]);
        }
    }
    for (unsigned i = 0; i < verts.size(); ++i)
    {
        std::set<unsigned> rmRedunt;
        for (std::vector<unsigned>::iterator iter = verts[i].adjVerts.begin();
             iter != verts[i].adjVerts.end(); ++iter)
            rmRedunt.insert(*iter);
        verts[i].adjVerts.clear();
        for (std::set<unsigned>::iterator iter = rmRedunt.begin();
             iter != rmRedunt.end(); ++iter)
            verts[i].adjVerts.push_back(*iter);
    }
    for (Edge2Faces::iterator iter = edge2Faces.begin(); iter != edge2Faces.end(); ++iter)
    {
        if (iter->second.size() == 1)
        {
            verts[iter->first.first].isBoundary = true;
            verts[iter->first.second].isBoundary = true;
        }
    }

}

void Mesh::Save(const char *fileName)
{
    std::ofstream output(fileName);
    for (unsigned i = 0; i < verts.size(); ++i)
        output << "v " << verts[i].pos.x << " " << verts[i].pos.y << " " << verts[i].pos.z << std::endl;
    for (unsigned i = 0; i < faces.size(); ++i)
        output << "f " << faces[i].verts[0] + 1 << " " << faces[i].verts[1] + 1 << " " << faces[i].verts[2] + 1
               << std::endl;
    std::cout << "Verts: " << verts.size() << std::endl;
    std::cout << "Faces: " << faces.size() << std::endl;
    output.close();
}

Vector3D Mesh::GetNormalTriangle(Face &f)
{
    Vector3D u = verts[f.verts[1]].pos - verts[f.verts[0]].pos;
    Vector3D v = verts[f.verts[2]].pos - verts[f.verts[0]].pos;

    return (u ^ v);
}

void Mesh::Init()
{
    glist = glGenLists(1);
    glNewList(glist, GL_COMPILE);
    {
        glPushMatrix();
        for (int i = 0; i < faces.size(); i++)
        {
            glBegin(GL_TRIANGLES);
            auto n = GetNormalTriangle(faces[i]);
            glNormal3f(n.x, n.y, n.z);
            for (int j = 0; j < 3; j++)
                glVertex3f(verts[faces[i].verts[j]].pos.x,
                           verts[faces[i].verts[j]].pos.y,
                           verts[faces[i].verts[j]].pos.z);
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
}

void Mesh::Render()
{
    static GLfloat rot = 0.0;

    glPushMatrix();
    glTranslatef(0, -2.0f, 6.5f);
    glColor4f(1.0, 0.33, 0.33, 1.0);
    glRotatef(rot, 0.0, 1.0, 0.0);
    glCallList(glist);
    glPopMatrix();

    rot = rot + 0.6f;
    if (rot > 360)
        rot -= 360;
}