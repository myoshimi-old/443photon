#include <string>

#include <cv.h>
#include <highgui.h>
#include "color.hpp"
#include "screen.hpp"
#include "vector3.hpp"

using namespace std;
using namespace cv;

// ===========================================================
// 視線ベクトルの生成 (いずれScreenクラスに移動)
// ===========================================================
Vector3 Screen::getViewVector(Vector3 viewPoint, int x, int y){
    Vector3 ret;
    Vector3 sp; // 画素のベクトル位置
    // スクリーンの左上から画素位置へのベクトルsp
    sp = (topright - topleft) * ((REAL)x / width)
        + (bottomleft - topleft) * ((REAL)y / height);
    ret = (topleft - viewPoint) + sp;
    /*
    cout << "  ScreenLocation : ";
    sp.disp();
    // 視線ベクトルの生成(スクリーン左上位置と，
    // そこからの画素へのベクトルと視点)
    cout << "  ViewVector(un) : ";
    ret.disp();
    */
    ret = ret.normalize();
    //ret.disp();
    return ret;
}

Screen::Screen(UINT32 w_, UINT32 h_){
    int i, j;
    width  = w_;
    height = h_;
    
    pixel = (Color*)malloc(sizeof(Color)*width*height);
    
    for(i=0;i<(int)height;i++){
        for(j=0;j<(int)width;j++){
            //pixel[i * width + j].setColor(rand()%255,
            //                              rand()%255,
            //                              rand()%255);
            pixel[i * width + j].setColor(0, 0, 0);
        }
    }
};

void Screen::writePng(string file){
  int x, y;
  Mat mat;
  Mat3b m;
  IplImage output;

  mat.create(height, width, CV_8UC3);
  m = mat;

  for(y=0;y<(int)height;y++){
    for(x=0;x<(int)width;x++){
      m(Point(x, y)) = Vec3b((int)pixel[y * width + x].blue,
                             (int)pixel[y * width + x].green,
                             (int)pixel[y * width + x].red);
    }
  }

  output = m;
  cvSaveImage(file.c_str(), &output);
}
