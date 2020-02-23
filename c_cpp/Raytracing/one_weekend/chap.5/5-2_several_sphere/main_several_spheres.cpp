#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include <float.h>

vec3 color( const ray& r,       //input: r⇒スクリーン上の1pixに向かうベクトル
            hitable *world)     //ヒット判定
{
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX, rec))
    {
        //入力光線rがどこかしらにヒットした場合、そこの単位法線ベクトルを正規化したカラー値として返す。
        return 0.5* vec3(rec.normal.x() + 1,rec.normal.y() + 1, rec.normal.z() + 1); 
    }
    else
    {
        //draw background
        vec3 unit_direction = unit_vector(r.direction());       //光線の単位方向ベクトル
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }    
}

int main()
{
    int ipix_size = 2000;
    int jpix_size = 1000;
    int object_num = 2;
    const char *filepath ="D:\\vsc\\c_cpp\\Raytracing\\one_weekend\\chap.5\\5-2_several_sphere\\out_several_hitable_fine.ppm";

    std::ofstream ofs(filepath);
    if(!ofs)
    {
        std::cout << "ファイルが開けませんでした。" << std::endl;
        std::cin.get();
        return 0;
    }
    else
    {
        //   std::cout << "P3\n" << nx << " " << ny << "\n255\n";
        ofs << "P3\n" << ipix_size << " " << jpix_size << "\n255\n";
        //スクリーンとカメラを用意する
        vec3 lower_left_corner(-2.0,-1.0,-1.0);     //スクリーンの開始位置。左下。
        vec3 horizontal(4.0, 0.0, 0.0);             //開始位置から水平にどんだけ移動するか。＝横幅
        vec3 vertical(0.0, 2.0, 0.0);               //開始位置から垂直にどんだけ移動するか。=縦幅
        vec3 origin(0.0, 0.0, 0.0);                 //原点位置、カメラ位置のこと。
        //hitable…衝突判定物体の数＝オブジェクトの数
        hitable *list[object_num];
        list[0] = new sphere(vec3(0, 0, -1), 0.5);          //球一つ目
        list[1] = new sphere(vec3(0, -100.5, -1), 100);     //球二つ目
        hitable *world = new hitable_list(list, object_num);
        for(int jpix = jpix_size - 1; jpix >= 0; jpix--)
        {
            for(int ipix = 0; ipix < ipix_size; ipix++)
            {
                //パラメータ(ex.p(t) = A + t*Bのt)
                float u = float(ipix) / float(ipix_size);                       //水平方向の割合
                float v = float(jpix) / float(jpix_size);                       //垂直方向の割合       
                ray r(origin, lower_left_corner + u*horizontal + v*vertical);    //カメラからスクリーン上の各ピクセルに飛ばした光線ベクトル
                

                vec3 col = color(r, world);        //カラーの取得[r_normal,g_normal,b_normal](値域0 ~ 1) 
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);
                
                ofs << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
}