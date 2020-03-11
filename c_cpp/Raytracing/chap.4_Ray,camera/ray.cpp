#include "ray.h"

//位置ベクトル、方向ベクトルで光線を指定
ray::ray(const vec3& a, const vec3& b)
{
    this->A = a;
    this->B = b;
}

//位置ベクトル取得
vec3 ray::origin() const
{
    return this->A;
}

//方向ベクトル取得
vec3 ray::direction() const
{
    return this->B;
}

//パラメータtで光線位置取得
vec3 ray::point_at_parameter(float t) const
{
    return A + t * B;
}
