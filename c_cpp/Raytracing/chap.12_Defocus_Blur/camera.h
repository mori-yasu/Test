#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"
#include "random.h"

//半径1の円盤上のランダムな位置ベクトルを作成する
vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(), random_double(), 0);
        if (p.squared_length() >= 1) continue;
        return p;
    }
}

//カメラクラスの作成
class camera
{
    public:
        camera( vec3 lookfrom,  //カメラ原点の位置ベクトル=従来のorigin 
                vec3 lookat,    //視線
                vec3 vup,       //ワールド座標垂直方向
                double vfov,    //垂直方向のfov.unit[deg]
                double aspect,  //アスペクト比
                double aperture,    //絞り
                double focus_dist)  //焦点距離
        {
            //コントラクタの引数に合わせるようにスクリーンの位置ベクトルを対応させる
            origin = lookfrom;  //カメラ原点
            lens_radius = aperture / 2.0;

            auto theta = vfov*3.1415926535/180; //deg2rad
            auto half_height = tan(theta/2);    //
            auto half_width = half_height * aspect;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));     //w―vup平面と直行する単位ベクトル(スクリーン水平方向)
            v = cross(w, u);                    //w-u平面と直行する単位ベクトル(スクリーン垂直方向)
            
            //スクリーンの用意
            lower_left_corner = origin - focus_dist*half_width*u - focus_dist*half_height*v - focus_dist*w;  //スクリーンの開始位置。左下。(-w … スクリーンを距離1の所においてるってことになってるから)
            horizontal = 2.0*half_width*focus_dist*u;             //開始位置から水平にどんだけ移動するか。＝横幅
            vertical = 2.0*half_height*focus_dist*v;               //開始位置から垂直にどんだけ移動するか。=縦幅
        }
        ray get_ray(float s, float t)
        {
            vec3 rd = lens_radius*random_in_unit_disk();    //仮想レンズ円筒上の始点位置ベクトル
            vec3 offset = u*rd.x() = v*rd.y();

            //原点のカメラからスクリーン上の各ピクセルに飛ばした光線ベクトル
            return  ray(this->origin + offset, 
                        this->lower_left_corner + s*this->horizontal + t*this->vertical - this->origin - offset);
        }

        vec3 lower_left_corner;
        vec3 horizontal;       
        vec3 vertical;
        vec3 origin;
        double lens_radius;
        vec3 u, v, w;       //任意の方向のカメラ上になす正規直交基底
};

#endif