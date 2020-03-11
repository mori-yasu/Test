#ifndef _HITABLE_H
#define _HITABLE_H

#include "ray.h"
//衝突判定の抽象クラス

class material; //マテリアルクラス(循環参照のケア)

struct hit_record
{
    float   t;    //パラメータ
    vec3    p;     //ベクトル
    vec3    normal;//法線単位ベクトル
    material *mat_ptr;  //マテリアルポインタ
};

//ヒット判定
class hitable
{
    public:
        virtual bool hit(   const ray& r,       //入射光線
                            float t_min,
                            float t_max,
                            hit_record& rec) const = 0;
    };

#endif
