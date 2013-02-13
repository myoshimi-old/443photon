#include "443ray.hpp"
#include "color.hpp"

/** @file color.hpp
    @class Color
    @brief 色表現クラス実装ファイル 
 */


/** @brief *演算子の再定義．
    ベクトルの各要素をスカラー倍する．
    @param[in] t 乗算する値
    @return 乗算された色のインスタンス
*/
Color Color::operator*(REAL t){
    Color ret;
    ret.setColor((UINT8)(red   * t)%256,
                 (UINT8)(green * t)%256,
                 (UINT8)(blue  * t)%256);
    return ret;
};

/** @brief +演算子の再定義．
    色の各要素を加算する
    @param[in] t 加算する色 
    @return 加算された色のインスタンス
*/
Color Color::operator+(Color c){
  Color ret;
  ret.setColor((UINT8)(red   + c.red)%256,
                (UINT8)(green + c.green)%256,
                (UINT8)(blue  + c.blue)%256);
  
  return ret;
};

/** @brief 初期化付きコンストラクタ
    @param[in]  r_ R値
    @param[in]  g_ G値
    @param[in]  b_ B値
*/
Color::Color(UINT8 r_, UINT8 g_, UINT8 b_){
    red = r_; green = g_; blue = b_;
};

/** @brief 色設定メソッド
    @param[in]  r_ R値
    @param[in]  g_ G値
    @param[in]  b_ B値
*/
void Color::setColor(UINT8 r_, UINT8 g_, UINT8 b_){
    red = r_; green = g_; blue = b_;
}
