#ifndef _INC_SCENE
#define _INC_SCENE

#include "omp.h"
#include "vector3.hpp"
#include "polygon3.hpp"
#include "color.hpp"
#include "aabb3.hpp"
#include "443ray.hpp"

using namespace std;

class Scene{
public:
    Vector3  vp;
    Vector3* vertex;
    Polygon3* face;
    AABB3** bbox;
    AABB3* tree;
    Vector3**  d_vec;
    int NumVertex;
    int NumFace;
    
    Scene(){};
    ~Scene(){};
    void load_ply(string filename);
    void generateTree();
    Polygon3* traversal(int id, AABB3* ptr, REAL* minDist,
                        Vector3 viewPoint, Vector3 viewVector);
    int partition(int s, int e, int flag);
    AABB3* division(int s, int e, int flag);
    void   sortingbox(int s, int e, int flag);
    Color shading(Vector3 view_vector,
                  Vector3 light, Vector3 n,
                  Color color, REAL s);
};

#endif

