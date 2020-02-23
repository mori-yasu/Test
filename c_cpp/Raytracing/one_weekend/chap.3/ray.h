#ifndef _RAY_H    //二重定義防止
#define _RAY_H

#include "vec3.h"

class ray
{
    public:
        //コンストラクタ
        ray(){}

        //位置ベクトル、方向ベクトルで光線を指定
        ray(vec3 const& a, vec3 const& b)
        {
            A = a;
            B = b;
        }

        //位置ベクトル取得
        vec3 origin() const
        {
            return A;
        }
        //方向ベクトル取得
        vec3 direction() const
        {
            return B;
        }
        //パラメータtで光線位置取得
        vec3 point_at_parameter(float t) const
        {
            return A + t * B;
        }

        vec3 A;
        vec3 B;

};
#endif
