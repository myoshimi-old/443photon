#ifndef _INC_POLYGON3
#define _INC_POLYGON3

#include "vector3.hpp"
#include "color.hpp"

//class Polygon3 : public Model{
class Polygon3{
public:
  Vector3 v1, v2, v3;
  Color color;
  Polygon3(){};
  Polygon3(Color* set_color, Vector3* v1_, Vector3* v2_, Vector3* v3_);
  REAL intersect(Vector3 viewpoint, Vector3 view_vector);
  Vector3 get_normal_vector(Vector3 np);
  void show();
  Vector3 getMax();
  Vector3 getMin();
};

#endif // _INC_POLYGON3
