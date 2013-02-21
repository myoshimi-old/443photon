#include<iostream>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<queue>
#include<stack>

#include"aabb3.hpp"
#include"scene.hpp"

#define ASCII  0
#define BINARY 1

/** @file  scene.cpp
 *  @brief シーンクラス実装ファイル
 */

/** @brief エンディアンの変換
    @param[in]  array 対象を文字型の配列として見たときのアドレス
    @param[in]  size  配列長(バイト数)
*/
void convertEndian(char* array, int size){
    char tmp;
    char *head, *tail;

    head = array;
    tail = array + size - 1;

    while(head < tail){
        tmp   = *head;
        *head = *tail;
        *tail = tmp;
        head++;
        tail--;
    }
};

/** @brief シェーディング
    @param[in]  view_vector 視線ベクトル
    @param[in]  light       光線ベクトル
    @param[in]  n           物体の法線ベクトル(単位ベクトル)
    @param[in]  color       物体の色
    @param[in]  s           重み
*/
Color Scene::shading(Vector3 view_vector,
                     Vector3 light, Vector3 n,
                     Color color, REAL s){
    REAL kd = 0.7, ks = 0.7, ke = 0.3;
    Color c, c0, c1;
    REAL ln, lv, nv;
    REAL cos_alpha, cos_beta, cos_beta_pow;
    REAL h;
    // c.set_color(200, 200, 200);

    ln = Vector3::dot(light, n);
    lv = Vector3::dot(light, view_vector);
    nv = Vector3::dot(n, view_vector);

    cos_alpha = ln * (-1.0);
    if(cos_alpha < 0.0){
        cos_alpha = 0.0;
    }

    cos_beta = ln * 2.0 * nv - lv;
    if(cos_beta < 0.0){
        cos_beta = 0.0;
    }
//    printf(" cb  : %5.4f\n", cos_beta);

    //cos_beta_pow = pow(cos_beta, 20.0);
    cos_beta_pow = pow(cos_beta, 20.0);
//    printf(" cbp : %5.4f\n", cos_beta_pow);

    h = (s * kd * cos_alpha + ke);
    
    c0 = color * h;
    c1.setColor(255,255,255); // 環境光
    c1 = c1 * (s * ks * cos_beta_pow);
    c = c0 + c1;
    return c;
};

/** @brief AABB3配列のソート
    @param[in]  s          開始要素
    @param[in]  e          終端要素+1
    @param[in]  flag       ソート対象指定フラグ
*/
void Scene::sortingbox(int s, int e, int flag){
    int l, r;
    Vector3* t;
    REAL pivot, lval, rval;
    AABB3* tbox;

    /*
    cout << " [" << s << " : " << e << "]  "
         << e - s 
         << "  (" << flag << ")" << endl;
    */
    l = s;
    r = e - 1;

    if(l < r){
        pivot = (d_vec[l]->getVector(flag)
                 + d_vec[r]->getVector(flag)) / 2.0;
        //cout << "  pivot : " << pivot << endl;
        
        while(l < r){
            rval = d_vec[r]->getVector(flag);
            //cout << "  R d_vec[" << r << "] : " << rval << endl;
            while(rval > pivot && l < r){
                r--;
                rval = d_vec[r]->getVector(flag);
                //cout << "  R d_vec[" << r << "] : " << rval << endl;
            }
            
            lval = d_vec[l]->getVector(flag);
            //cout << "  L d_vec["<< l << "] : " << lval << endl;
            while(lval < pivot && l < r){
                l++;
                lval = d_vec[l]->getVector(flag);
                //cout << "  L d_vec[" << l << "] : " << lval << endl;
            }
            
            t = d_vec[r];
            d_vec[r] = d_vec[l];
            d_vec[l] = t;
            
            tbox = bbox[r];
            bbox[r] = bbox[l];
            bbox[l] = tbox;
            
            r--;
            l++;
        }
        
        sortingbox(s, s+(e-s)/2, flag);
        sortingbox(s+(e-s)/2, e, flag);
    }
}

void Scene::genTreeGraph(){
    AABB3* ptr;
    int i;
    char str[256];
    queue<AABB3*> q;
    stack<AABB3*> s;

    s.push(tree);

    while(!s.empty()){
        ptr = s.top();
        s.pop();
        q.push(ptr);
        if(ptr->left != NULL){
            s.push(ptr->left);
        }
        if(ptr->right != NULL){
            s.push(ptr->right);
        }
    }
    
    printf("digraph sample {\n");
    printf("  node [shape=record];\n");

    ptr  = tree;
    i = 1;

    while(!q.empty()){
        ptr = q.front();
        ptr->getGraph(str, i);
        printf("%s", str);
        if(i != 1){
            printf("  s%d:m%d->s%d:n%d;\n", i/2, i/2, i, i);
        }
        q.pop();
        i++;
    }



/*
    gptr = new AABB3Graph();
    gptr->add(i, ptr);
    printf(gptr->str);

    ptr  = ptr->left;
    gptr = gptr->next;
    i    = 2*i;

    gptr = new AABB3Graph();
    gptr->add(i, ptr);
    printf(gptr->str);
    
    printf("  s%d:m%d->s%d:n%d;\n", i, i, 2*i+1, 2*i+1);


    ptr->right->getGraph(&s[0], 2*i+2);
    printf("%s", s);
    printf("  s%d:m%d->s%d:n%d;\n", i, i, 2*i+2, 2*i+2);
    */
    
    printf("}\n");
};

/** @brief トラバーサル処理
    @param[in]  id ノード番号
    @param[in]  ptr トラバーサル対象AABB3ノードへのポインタ
    @param[in,out] minDist 現在の交差最短距離
    @param[in]  viewPoint 視点(レイ照射開始点)
    @param[in]  viewVector 視線ベクトル
*/
Polygon3* Scene::traversal(int id, AABB3* ptr, REAL* minDist,
                           Vector3 viewPoint, Vector3 viewVector){
    
    Polygon3* ret;
    Polygon3* tmp;

    REAL d;
    REAL dn, dr, dl;

    ret = NULL;

    if(ptr != NULL){
        d = ptr->intersect(viewPoint, viewVector);
        if(d > 0.0){
            if(ptr->node != NULL){
                dn = ptr->node->intersect(viewPoint, viewVector);
                if(dn > 0.0 && dn < *minDist){
                    *minDist = dn;
                    ret      = ptr->node;
                    // cout << "    " << id << " : "<< dn << endl;
                }
            }
            else{
                dr = *minDist;
                tmp = traversal(id*2, ptr->right, &dr,
                                 viewPoint, viewVector);
                if(tmp != NULL){
                    if(dr < *minDist){
                        *minDist = dr;
                        ret = tmp;
                    }
                }

                dl = *minDist;
                tmp = traversal(id*2+1, ptr->left, &dl,
                                 viewPoint, viewVector);
                if(tmp != NULL){
                    if(dl < *minDist){
                        *minDist = dl;
                        ret = tmp;
                    }
                }
            }
        }
    }
    return ret;
};

AABB3* Scene::division(int s, int e, int flag){
    AABB3* ret;

    //cout << "[" << s << ", " << e << "] : " << e-s << endl;
    
    if(s+1 >= e){
        ret = bbox[s];
    }
    else{
        ret = new AABB3();
        ret->empty();
        
        sortingbox(s, e, flag);
        
        //cout << "a ";
        ret->left  = division(s, s+(e-s)/2, (flag+1)%3);
        //cout << "b ";
        ret->right = division(s+(e-s)/2, e, (flag+1)%3);

        // aabb3の箱の大きさの設定
        ret->add(ret->left->max);
        ret->add(ret->right->max);
        ret->add(ret->left->min);
        ret->add(ret->right->min);
    }
    
    return ret;
};


void Scene::generateTree(){
    // ポリゴンを覆う最小のAABBを作成する
    // 木の段数：ceil(log2(NumFace)/log2(n))
    // nodeLevel = ceil(log2(NumFace)/log2(n));
    // nodeNum   = (int)pow((REAL)n, (REAL)nodeLevel);

    bbox = (AABB3**)malloc(sizeof(AABB3*) * NumFace);
    
    cout << "Acclocated " << NumFace;
    cout << " boxes of AABB3" << endl;

    // bbox = &tree[nodeNum];

    // 最小ポリゴンを覆うAABB3ボックスを作成
    for(int i=0;i<NumFace;i++){
        bbox[i] = new AABB3();
        bbox[i]->empty();
        bbox[i]->add(face[i].getMax());
        bbox[i]->add(face[i].getMin());
        bbox[i]->node = &face[i];
    }

    d_vec = (Vector3**)malloc(sizeof(Vector3*)*NumFace);
    for(int i=0;i<NumFace;i++){
        d_vec[i] = new Vector3(bbox[i]->get_gravity_center().x,
                               bbox[i]->get_gravity_center().y,
                               bbox[i]->get_gravity_center().z);
    }

    cout << NumFace << endl;
    
    tree = division(0, NumFace, 0);
}

/** @brief plyファイルの読み込み
 *  @param[in] file 出力ファイル名
 */
void Scene::load_ply(string filename){
    int i;
    FILE* fp;
    int N = 256;
    char line[N];
    char* c[64];
    UINT8 plyformat;
    
    cout << "Loading " << filename << " ..."<< endl; 
    fp = fopen(filename.c_str(), "r");
    if(fp == NULL){
        printf("%sファイルが開けません\n", filename.c_str());
        exit(-1);
    }

    while(fgets(line, N, fp) != NULL){
        line[strlen(line) - 1] = '\0'; // 改行コード削除

        // 半角スペース区切りで切り出し
        i = 0; c[i] = strtok(line, " ");
        while(c[i] != NULL){
            i++; c[i] = strtok(NULL, " ");
        }

        i = 0;
        while(c[i] != NULL){
            printf("%s ", c[i]);
            i++;
        }
        printf("\n");

        // format要素：フォーマット
        if(strcmp("format", c[0])==0){
            if(strcmp("ascii", c[1])==0) plyformat = ASCII;
            else if(strncmp("binary", c[1], 6)==0) plyformat = BINARY;
        }
        // element要素：ポリゴン数と頂点数の読み込み
        if(strcmp("element", c[0]) == 0){
            if(strcmp("face", c[1]) == 0) NumFace = atoi(c[2]);
            else if(strcmp("vertex", c[1]) == 0) NumVertex = atoi(c[2]);
        }
        if(strcmp("end_header", c[0]) == 0) break;
    }

    cout << "  File Format : ";
    if(plyformat == ASCII) cout << "ASCII";
    else if(plyformat == BINARY) cout << "BINARY";
    cout << endl;
    cout << "  Vertex : " << NumVertex << endl;
    cout << "  Face   : " << NumFace << endl;

    vertex = (Vector3*)malloc(sizeof(Vector3)*NumVertex);
    face   = (Polygon3*)malloc(sizeof(Polygon3)*NumFace);
    
    // ASCII-plyの場合の処理
    if(plyformat == ASCII){
        // 頂点位置の設定
        for(int j=0;j<NumVertex;j++){
            if(fgets(line, N, fp) == NULL) exit(-1);
            line[strlen(line) - 1] = '\0'; // 改行コード削除
            // 半角スペース区切りで切り出し
            i = 0; c[i] = strtok(line, " ");
            while(c[i] != NULL){
                i++; c[i] = strtok(NULL, " ");
            }
            vertex[j].x = atof(c[0]);
            vertex[j].y = atof(c[1]);
            vertex[j].z = atof(c[2]);
        }
        // ポリゴンの設定
        for(int j=0;j<NumFace;j++){
            if(fgets(line, N, fp) == NULL) exit(-1);
            line[strlen(line) - 1] = '\0'; // 改行コード削除
            // 半角スペース区切りで切り出し
            i = 0; c[i] = strtok(line, " ");
            while(c[i] != NULL){
                i++; c[i] = strtok(NULL, " ");
            }
            face[j].v1 = vertex[atoi(c[1])];
            face[j].v2 = vertex[atoi(c[2])];
            face[j].v3 = vertex[atoi(c[3])];
        }
    }
    else if(plyformat == BINARY){
        for(int j=0;j<NumVertex;j++){
            // 20バイト
            fread(line, sizeof(unsigned char), 20, fp);
            //convertEndian(line+0, sizeof(float));

            /*
            for(int i=0;i<20;i++){
                printf("%02X", (unsigned char)line[i]);
            }
            printf(" : ");
            printf("%8.7f ", *(float*)(line+0));
            printf("%8.7f ", *(float*)(line+4));
            printf("%8.7f ", *(float*)(line+8));
            printf("\n");
            */
            vertex[j].x = *(float*)(line+0);
            vertex[j].y = *(float*)(line+4);
            vertex[j].z = *(float*)(line+8);
        }
        for(int j=0;j<NumFace;j++){
            // 13バイト
            fread(line, sizeof(unsigned char), 13, fp);
            /*
            for(int i=0;i<13;i++){
                printf("%02X", (unsigned char)line[i]);
            }
            printf(" t%d ", *(unsigned char*)(line+0));
            printf("%d \n", *(unsigned int*)(line+1));
            */
            face[j].v1 = vertex[*(unsigned int*)(line+1)];
            face[j].v2 = vertex[*(unsigned int*)(line+5)];
            face[j].v3 = vertex[*(unsigned int*)(line+9)];
        }
    }
    
    fclose(fp);
};

