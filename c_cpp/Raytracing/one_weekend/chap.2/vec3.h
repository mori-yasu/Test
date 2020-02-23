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
inline std::istream& operator>>(std::istream &is, vec3 &t);
//出力
inline std::ostream& operator<<(std::ostream &os, const vec3 &t);
//ベクトル和
inline vec3 operator+(const vec3 &v1, const vec3 &v2);
//ベクトル差
inline vec3 operator-(const vec3 &v1, const vec3 &v2);
//要素積
inline vec3 operator*(const vec3 &v1, const vec3 &v2);
//要素商
inline vec3 operator/(const vec3 &v1, const vec3 &v2);
//定数倍
inline vec3 operator*(float coef, const vec3 &v);
//定数割
inline vec3 operator/(vec3 v, float coef);
//定数倍
inline vec3 operator*(const vec3 &v, float coef);
//内積計算
inline float dot(const vec3 &v1, const vec3 &v2 );
//外積計算
inline vec3 cross(const vec3 &v1, const vec3 &v2 );
inline vec3 unit_vector(vec3 v);