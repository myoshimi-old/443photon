#include<iostream>
#include<string>
#include<cmath>
#include<stdlib.h>

#include"443ray.hpp"
#include"443photon.hpp"
#include"screen.hpp"
#include"scene.hpp"
#include"light.hpp"

using namespace std;

double get_dtime(void);

/** @file main.cpp
    @brief main関数
           フォトンマップの生成
 */
int main(int argc, char** argv){
    REAL d0, d1, d2, d3, d4;
    UINT32 screenWidth, screenHeight;
    string inputFilename, outputFilename;
    // コマンドライン引数の読み込み
    if(argc != 5){
        cout << argv[0]
             << " [width] [height] [file.ply] [file.{ppm,png}]"
             << endl;
        exit(1);
    }
    screenWidth  = atoi(argv[1]);
    screenHeight = atoi(argv[2]);
    inputFilename = argv[3];
    outputFilename = argv[4];
    
    srand((unsigned int)time(NULL));
    
    

    // スクリーンの設定
    Screen *screen;
    // スクリーンサイズの設定
    screen = new Screen(screenWidth, screenHeight);
    // スクリーン位置の設定
    screen->topleft.setVector(    -0.10,  0.12, 0.7);
    screen->bottomleft.setVector( -0.10,  0.02, 0.7);
    screen->topright.setVector(    0.06,  0.12, 0.7);
    screen->bottomright.setVector( 0.06,  0.02, 0.7);
    
    // 光源の設定
    Scene *scene;
    scene = new Scene();

    d0 = get_dtime();
    scene->load_ply(inputFilename);
    
    d1 = get_dtime();
    scene->generateTree();
    scene->tree->disp();
    // 視点の設定
    scene->vp.setVector(0.0, 0.03, 1.5);
    cout << "  ViewPoint : ";
    scene->vp.disp();

    // 光源の設定
    Light *light;
    light = new Light();
    light->setPosition(*(new Vector3(2.0, 2.0, 0.0)));
    
    Vector3 vv; // 視線ベクトル
    Polygon3* p; // 交差ポリゴン
    REAL dist; // 交差時のポリゴンとの距離
    
    d2 = get_dtime();
    
    Vector3 np, n, lv;
    Color c;
    int x;
    // 画素値の設定
#ifdef _OPENMP
#pragma omp parallel for private(x, vv, dist,p,np,n,lv,c)
#endif
    for(int y=0;y<(int)screen->height;y++){
        for(x=0;x<(int)screen->width;x++){
            // 視線ベクトルの生成
            vv = screen->getViewVector(scene->vp, x, y);
            // cout << "===[" << j << ", " << i << "]===" << endl;
            // =====================================================
            // 交差判定
            // =====================================================
            // 全てのポリゴンとガチる
            /*
            for(int k=0;k<scene->NumFace;k++){
                REAL pdist = scene->face[k].intersect(scene->vp, vv);
                if(pdist < dist){
                    min_id   = k;
                    dist = dist;
                }
            }
            */
            // AABB3ツリーと交差判定
            //cout << "===[" << j << ", " << i << "]===" << endl;
            
            dist = HUGE_VAL;
            p = scene->traversal(1, scene->tree, &dist,
                                 scene->vp, vv);

            if(dist > 0.0 && dist < 100000.0){
                // 交点(視点から交点へのベクトル)を求める
                // 視線ベクトルをスカラー倍したベクトル
                np = scene->vp + (vv * dist);
                // 物体の法線ベクトル(単位ベクトル)の計算
                n = p->get_normal_vector(np);
                // 光線ベクトル
                lv = np - light->getPosition();
                lv = lv.normalize();

                c = scene->shading(vv, lv, n,
                                   *(new Color(255,255,255)),
                                   0.5);
                // printf("%d %d %d\n", c.red, c.green,c.blue);
                screen->pixel[y*screen->width+x].setColor(c.red,c.green, c.blue);
            }
            else{
                screen->pixel[y*screen->width+x].setColor(0,0,0);
            }


            
        }
    }

    d3 = get_dtime();
    
    screen->writePng(outputFilename);
    
    d4 = get_dtime();
    
    cout << "Loading PLY  : ,     " << d1 - d0 << ", [sec]" << endl;
    cout << "Building BVH : ,     " << d2 - d1 << ", [sec]" << endl;
    cout << "Intersect    : ,     " << d3 - d2 << ", [sec]" << endl;
    cout << "Generation   : ,     " << d4 - d3 << ", [sec]" << endl;
    cout << "Total        : ,     " << d4 - d0 << ", [sec]" << endl;
    return 0;
}
