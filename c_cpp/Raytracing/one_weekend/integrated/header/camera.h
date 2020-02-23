#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"

//カメラモデル
class camera
{
    public:
        camera()
        {
            //スクリーンとカメラを用意する
            lower_left_corner = vec3(-2.0,-1.0,-1.0);     //スクリーンの開始位置。左下。
            horizontal = vec3(4.0, 0.0, 0.0);             //開始位置から水平にどんだけ移動するか。＝横幅
            vertical = vec3(0.0, 2.0, 0.0);               //開始位置から垂直にどんだけ移動するか。=縦幅
            origin = vec3(0.0, 0.0, 0.0);                 //原点位置、カメラ位置のこと。
        }
        ray get_ray(float u, float v)
        {
            //原点のカメラからスクリーン上の各ピクセルに飛ばした光線ベクトル
            return  ray(this->origin, 
                        this->lower_left_corner + u*this->horizontal + v*this->vertical - this->origin);    
        }

        vec3 lower_left_corner;
        vec3 horizontal;       
        vec3 vertical;
        vec3 origin;
};

#endif