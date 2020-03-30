#ifndef _RAY_H
#define _RAY_H

#include "vec3.h"

class ray
{
    public:
        //コンストラクタ
        ray()
        {
        }
        //位置ベクトル、方向ベクトルで光線を指定
        ray(const vec3& a, const vec3& b)
        {
            this->A = a;
            this->B = b;
        }

        //位置ベクトル取得
        vec3 origin() const
        {
            return this->A;
        }
        //方向ベクトル取得
        vec3 direction() const
        {
            return this->B;
        }
        //パラメータtで光線位置取得
        vec3 point_at_parameter(float t) const
        {
            return A + t*B;
        }

        vec3 A;
        vec3 B;

};

#endif