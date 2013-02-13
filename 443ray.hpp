#ifndef _INC_443RAY
#define _INC_443RAY

/** @file 443ray.hpp
    @brief マクロ定義
 */

#define REAL double
#define UINT8 unsigned char
#define UINT32 unsigned int
#define sindex (y * (int)screen.width + x)
#define MIN2(x,y) ((x)<(y))? (x):(y)
#define MAX2(x,y) ((x)>(y))? (x):(y)
#define MIN3(x,y,z) (MIN2(x, MIN2(y, z)))
#define MAX3(x,y,z) (MAX2(x, MAX2(y, z)))

//#define BVH_LIST

#endif
