#ifndef _INC_SCREEN
#define _INC_SCREEN

/**
 * The screen class represents a screen
 *
 * \author Masato Yoshimi
 */

#include <string>
#include "443ray.hpp"
#include "color.hpp"
#include "vector3.hpp"

using namespace std;

/** @file */

/** @class Screen
 *  @brief スクリーンクラス
 */
class Screen{
public:
    UINT32 width;
    UINT32 height;
    Color* pixel;
    Vector3 topleft, topright, bottomleft, bottomright;
    /** @brief コンストラクタ
     *  @param[in] w_ スクリーン幅
     *  @param[in] h_ スクリーン高さ
     */
    Screen(UINT32 w_, UINT32 h_);
    /** @brief 視線ベクトルの計算 
     *  @param[in] viewPoint 視点位置 
     *  @param[in] x x軸上の画素位置
     *  @param[in] y y軸上の画素位置
     */
    Vector3 getViewVector(Vector3 viewPoint, int x, int y);
    /** @brief 画素情報からPNGファイルの生成
     *  @param[in] file 出力ファイル名
     */
    void writePng(string file);
};

#endif
