#ifndef _RANDOM_H
#define _RANDOM_H

#include <cstdlib>
#include "hitable.h"

//ランダムな0～1の乱数を生成する
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

//rejection method
//原点にある単位球内のランダムベクトルを取得する方法
vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        //単位立方体の中のランダムなベクトル
        p = 2.0*vec3(random_double(), random_double(), random_double()) - vec3(1, 1, 1);
    }
    while(p.squared_length() >= 1.0);   //生成したベクトルが単位球に含まれていない場合はやり直し
    return p;
}

#endif