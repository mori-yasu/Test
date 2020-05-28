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

//屈折ベクトルの計算
vec3 reflact(const vec3& uv, const vec3& n, double etai_over_etat)
{
    auto cos_theta = dot(-uv, n);   //A・B = |A||B|cosΘ = cosΘ (where |A| = |B| = 1)
    vec3 r_parallel = etai_over_etat*(uv + (cos_theta*n));   //屈折光の平行成分
    vec3 r_perp = -sqrt(1.0 - r_parallel.squared_length())*n;   //屈折光の垂直成分
    return r_parallel + r_perp;
}

//Schlickの近似(Fresnelの法則をだいぶ簡単にしたやつ。反射率の角度依存を表現する)
double schlick(double cosine, double ref_idx)
{
    auto r0 = (1 - ref_idx)/(1 + ref_idx);
    r0 = r0*r0;
    return r0 + (1 - r0)*pow((1 - cosine), 5);
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

//屈折(ガラス物体)
class dielectric: public material
{
        public:
            dielectric(double ri): ref_idx(ri){}    //コンストラクタ　引数屈折率のみ
            virtual bool scatter(   const ray& r_in,
                                    const hit_record& rec,
                                    vec3& attenuation,  //減衰率
                                    ray& scattered) const
            {
                attenuation = vec3(1.0, 1.0, 1.0); //ガラスとか減衰させない
                double etai_over_etat;
                if(rec.front_face)
                {
                    etai_over_etat = 1.0 / ref_idx;
                }
                else
                {
                    etai_over_etat = ref_idx;
                }
                vec3 unit_direction = unit_vector(r_in.direction());
                double cos_theta = dot(-unit_direction, rec.normal);
                double sin_theta = 0.0;
                if(cos_theta < 1.0)
                {
                    sin_theta = sqrt(1 - cos_theta*cos_theta);  //三平方
                }
                //全反射か屈折か判定
                if(etai_over_etat*sin_theta > 1.0)
                {
                    //必ず(全)反射。屈折率>1,入射角大の時におこる
                    vec3 reflected = reflect(unit_direction, rec.normal);
                    scattered = ray(rec.p, reflected);
                    return true; 
                }
                else
                {
                    //フレネル反射を考慮
                    double reflect_prob = schlick(cos_theta, etai_over_etat);
                    if (0)//random_double() < reflect_prob)
                    {
                        vec3 reflected = reflect(unit_direction, rec.normal);
                        scattered = ray(rec.p, reflected);
                        return true;
                    }
                    //屈折(when possible)
                    vec3 reflacted = reflact(unit_direction, rec.normal, etai_over_etat);
                    scattered = ray(rec.p, reflacted);
                    return true;
                }
            }
            double ref_idx;
};

#endif