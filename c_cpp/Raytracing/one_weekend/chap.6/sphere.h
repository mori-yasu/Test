#ifndef _SPHERE_H
#define _SPHERE_H

#include "hitable.h"

//球クラス
class sphere: public hitable
{
    public:
     sphere(){}
     sphere(vec3 cen, float r) : center(cen), radius(r){};
     virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
     vec3 center;
     float radius;
};

//球のヒット判定
//t*t*dot(B, B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0の二次方程式の解
bool sphere::hit(   const ray& r,       //入射光線
                    float t_min,
                    float t_max,
                    hit_record& rec) const
{
    vec3 oc = r.origin() - this->center;            //カメラ―球中心の方向ベクトル
    float a = dot(r.direction(), r.direction());    //dot(B, B)
    float b = 2.0*dot(oc, r.direction());         //2.0*dot(B,A-C)
    float c = dot(oc, oc) - radius * radius;        //dot(A-C,A-C) - R*R
    float discriminant = b*b - 4*a*c;
    if(discriminant > 0)    //球表面に接触
    {
        float temp = (-b - sqrt(discriminant))/(2.0*a);   //接触する最近のt
        if(temp < t_max && temp > t_min)
        {
            //recに保存
            rec.t = temp;                                       //パラメータt
            rec.p = r.point_at_parameter(rec.t);                 //球表面へのベクトル
            rec.normal = (rec.p - this->center) / this->radius; //球表面の単位法線ベクトル
            return true;
        }
        temp = (-b + sqrt(discriminant))/(2.0*a);        //接触する最遠のt
        if(temp < t_max && temp > t_min)
        {
            //recに保存
            rec.t = temp;                                       //パラメータt
            rec.p = r.point_at_parameter(temp);                 //球表面へのベクトル
            rec.normal = (rec.p - this->center) / this->radius; //球表面の単位法線ベクトル
            return true;
        }
    }
    //急に接触していない
    return false;
}

#endif