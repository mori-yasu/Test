#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "hitable.h"
#include "random.h"
#include "ray.h"

struct hit_record;

//全反射の方向を決める
vec3 reflect(   const vec3& v,  //入射ベクトル
                const vec3& n)  //単位法線ベクトル
{
    return v - 2*dot(v, n)*n;
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


//マテリアルの抽象クラス
class material{
    public:
        virtual bool scatter(
            const ray& r_in,
            const hit_record& rec,
            vec3& attenuation,  //減衰
            ray& scattered) const = 0;
};


//ランバートモデル(表面での拡散を等方的な反射と仮定)
class lambertian: public material
{
    public:
        lambertian(const vec3& a): albedo(a) {}
        //散乱モデル
        virtual bool scatter(   const ray& r_in,
                                const hit_record& rec,
                                vec3& attenuation,  //減衰率
                                ray& scattered) const
        {
            vec3 target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p, target - rec.p);     //入射光は、次はランダム方向に散乱する
            attenuation = albedo;
            return true;
        }

        vec3 albedo;    //アルベド…反射光/入射光
};

class metal: public material
{
        public:
            metal(const vec3& a, float f): albedo(a){
                if(f < 1)
                {
                    fuzz = f;
                }
                else
                {
                    fuzz = 1;
                }
            }
            //散乱モデル
            virtual bool scatter(   const ray& r_in,
                                    const hit_record& rec,
                                    vec3& attenuation,  //減衰率
                                    ray& scattered) const
            {
                //反射ベクトル
                vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
                //scattered = ray(rec.p, reflected);      //入射光は、次は全反射する
                scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());   //fuzziness(0～1)で反射光をブレさせる。
                attenuation = albedo;
                return (dot(scattered.direction(), rec.normal) > 0);
            }

            vec3 albedo;    //アルベド…反射光/入射光
            float fuzz;     //ぼやけ具合
};

#endif