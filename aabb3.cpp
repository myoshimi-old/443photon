#include<iostream>
#include<cmath>

#include"aabb3.hpp"

using namespace std;

/** @file */

bool AABB3::cmpx(AABB3* a, AABB3* b){
  bool ret=false;
  if(a->max.x < b->max.x){
    ret = true;
  }
  return ret;
}

AABB3* AABB3::clone(){
  AABB3* v;
  v = new AABB3();
  v->max.setVector(max.x, max.y, max.z);
  v->min.setVector(min.x, min.y, min.z);
  v->right = right;
  v->left = left;
  v->node = node;
  return v;
};

void AABB3::disp(){
    cout << "max: ";
    max.disp();
    cout << "min: ";
    min.disp();
};

void AABB3::getGraph(char* str, int n){
    char  s1[32];
    char  s2[32];
    max.getGraph(s1);
    min.getGraph(s2);
    sprintf(str, "  s%d [label=\""
            "{<n%d>|x|y|<m%d>z}|"
            "{max|%s}|{min|%s}\"];\n",
            n, n, n,s1,s2);
};

void AABB3::empty(){
    right = NULL;
    left  = NULL;
    node  = NULL;
    max.setVector(-HUGE_VAL, -HUGE_VAL, -HUGE_VAL);
    min.setVector(HUGE_VAL, HUGE_VAL, HUGE_VAL);
};

Vector3 AABB3::get_gravity_center(){
  Vector3 v;
  v.x = (max.x + min.x) / 2.0;
  v.y = (max.y + min.y) / 2.0;
  v.z = (max.z + min.z) / 2.0;
  return v;
};

void AABB3::add(Vector3 p){
  if(p.x < min.x) min.x = p.x;
  if(p.x > max.x) max.x = p.x;
  if(p.y < min.y) min.y = p.y;
  if(p.y > max.y) max.y = p.y;
  if(p.z < min.z) min.z = p.z;
  if(p.z > max.z) max.z = p.z;
};

REAL AABB3::intersect(Vector3 viewpoint, Vector3 view_vector){
  REAL tmp;
  REAL txs, txe;
  REAL tys, tye;
  REAL tzs, tze;
  REAL tin, tout; // incidence outgoing
  REAL dist;

  txs = (min.x - viewpoint.x) / view_vector.x;
  txe = (max.x - viewpoint.x) / view_vector.x;

  tys = (min.y - viewpoint.y) / view_vector.y;
  tye = (max.y - viewpoint.y) / view_vector.y;

  tzs = (min.z - viewpoint.z) / view_vector.z;
  tze = (max.z - viewpoint.z) / view_vector.z;

  // 数値が大きい方がe, 小さい方がsになるように調整
  if(txs > txe){tmp = txs; txs = txe; txe = tmp;}
  if(tys > tye){tmp = tys; tys = tye; tye = tmp;}
  if(tzs > tze){tmp = tzs; tzs = tze; tze = tmp;}

  // 最遠の入射スラブ
  tin = MAX3(txs, tys, tzs);
  /*
  tin = txs;
  if(tin < tys) tin = tys;
  if(tin < tzs) tin = tzs;
  */

  // 最近の出射スラブ
  tout = MIN3(txe, tye, tze);
  /*
  tout = txe;
  if(tout > tye) tout = tye;
  if(tout > tze) tout = tze;
  */

  dist = tout - tin;

  /*
  if(judge < 0.0){
    ret = false;
  }
  
  cout << " " << tout << " - " << tin << " = " << judge
       << " " << ret << endl;
  */
  
  return dist;
};
