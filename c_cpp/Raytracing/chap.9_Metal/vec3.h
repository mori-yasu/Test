#ifndef _VEC3_H
#define _VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

/*―――――――――――――――――――vec3のクラス定義―――――――――――――――――――*/
class vec3
{
    public:
    vec3()
    {
    }

    //値のセット
    vec3(float e0, float e1,float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    inline float x() const{ return e[0]; }
    inline float y() const{ return e[1]; }
    inline float z() const{ return e[2]; }
    inline float r() const{ return e[0]; }
    inline float g() const{ return e[1]; }
    inline float b() const{ return e[2]; }

    //
    inline const vec3& operator+() const { return *this; }  //自身のアドレスを返す
    inline const vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }   //クラスを返す
    inline float operator[](int i) const { return e[i]; }   //指定要素を返す
    inline float& operator[](int i) { return e[i]; }          //指定要素のアドレスを返す

    inline vec3& operator+=( const vec3 &v2 );
    inline vec3& operator-=( const vec3 &v2 );
    inline vec3& operator*=( const vec3 &v2 );
    inline vec3& operator/=( const vec3 &v2 );
    inline vec3& operator*=( const float t );
    inline vec3& operator/=( const float t );
 
   //距離
    inline float length() const
    {
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
 
    //二乗距離
    inline float squared_length() const
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    //単位ベクトルの作成
    inline void make_unit_vector();

    float e[3];
};

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