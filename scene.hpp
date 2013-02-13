#ifndef _INC_SCENE
#define _INC_SCENE

#include "omp.h"
#include "vector3.hpp"
#include "polygon3.hpp"
#include "color.hpp"
#include "aabb3.hpp"
#include "443ray.hpp"

using namespace std;



/** @file scene.hpp
 *  @class Scene
 *  @brief シーンクラスヘッダ
 */
class Scene{
public:
    Vector3  vp; //!< 視点位置 
    Vector3* vertex; //!< 頂点位置の配列
    Polygon3* face;  //!< ポリゴンの配列 
    AABB3** bbox;    //!< BVH (Bounding Volume Hierarchy)
    AABB3* tree;     //!< BVHのルートへのポインタ
    Vector3**  d_vec; //!< ソート対象となるデータの配列
    int NumVertex; //!< 頂点数
    int NumFace; //!< ポリゴン数
    
    /** @brief コンストラクタ
     */
    Scene(){};
    /** @brief デストラクタ
     */
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

