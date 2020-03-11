#include <iostream>
#include <stdlib.h>
#include <float.h>
#include "random.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

vec3 color( const ray& r,       //input: r⇒スクリーン上の1pixに向かうベクトル
            hitable *world)     //ヒット判定
{
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX, rec))
    {
        //rejection methodによって表面でランダム拡散
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5* color(ray(rec.p, target - rec.p), world);
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
    int itr_num = 100;
    int object_num = 2; //物体数
    const char *filepath ="D:\\workspace\\vsc\\c_cpp\\Raytracing\\one_weekend\\chap.7_DiffuseMaterials\\out_defuse_material.ppm";

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

        //hitable…衝突判定物体の数＝オブジェクトの数
        hitable *list[object_num];
        list[0] = new sphere(vec3(0, 0, -1), 0.5);          //球一つ目
        list[1] = new sphere(vec3(0, -100.5, -1), 100);     //球二つ目
        hitable *world = new hitable_list(list, object_num);
        camera cam;
        for(int jpix = jpix_size - 1; jpix >= 0; jpix--)
        {
            for(int ipix = 0; ipix < ipix_size; ipix++)
            {
                vec3 col(0, 0, 0);
                //アンチエイリアスのために指定回数ランダムに光線をブレさせる
                for(int itr = 0; itr < itr_num; itr++)
                {
                    srand(123L);    //初期化
                    float u = float(ipix + random_double()) / float(ipix_size);      //水平方向の割合
                    float v = float(jpix + random_double()) / float(jpix_size);      //垂直方向の割合
                    ray r = cam.get_ray(u, v);
                    col += color(r, world);
                }
                col /= float(itr_num);  //カラーは周辺の平均値
                
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);

                ofs << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
}