#ifndef _VEC3_H
#define _VEC3_H

#include "vec3.h"

/*―――――――――――――――――――以下メソッドの定義―――――――――――――――――――*/

//入力
inline std::istream& operator>>(std::istream &is, vec3 &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

//出力
inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

//単位ベクトルの作成
inline void vec3::make_unit_vector()
{
    float coef = 0.0;
    //ノルムの計算
    if((e[0]*e[0] + e[1]*e[1] + e[2]*e[2]) > 0)
    {
        coef = 1.0f / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);

        e[0] = e[0]*coef; e[1] = e[1]*coef; e[2] = e[2]*coef;
    }
}

//ベクトル和
inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

//ベクトル差
inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

//要素積
inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

//要素商
inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

//定数倍
inline vec3 operator*(float coef, const vec3 &v)
{
    return vec3(coef * v.e[0], coef * v.e[1], coef * v.e[2]);
}

//定数割
inline vec3 operator/(vec3 v, float coef)
{
    return vec3(v.e[0] / coef, v.e[1] / coef, v.e[2] / coef);
}

//定数倍
inline vec3 operator*(const vec3 &v, float coef)
{
    return vec3(coef * v.e[0], coef * v.e[1], coef * v.e[2]);
}

//内積計算
inline float dot(const vec3 &v1, const vec3 &v2 )
{
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

//外積計算
inline vec3 cross(const vec3 &v1, const vec3 &v2 )
{
    return vec3((v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}


inline vec3& vec3::operator+=(const vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float coef)
{
    e[0] *= coef;
    e[1] *= coef;
    e[2] *= coef;
    return *this;
}

inline vec3& vec3::operator/=(const float coef)
{
    e[0] /= coef;
    e[1] /= coef;
    e[2] /= coef;
    return *this;
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}
#endif