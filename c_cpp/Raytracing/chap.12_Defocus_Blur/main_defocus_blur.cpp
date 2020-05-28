#include <iostream>
#include <stdlib.h>
#include <float.h>
#include "random.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

vec3 color( const ray& r,       //input: r⇒スクリーン上の1pixに向かうベクトル
            hitable *world,     //ヒット判定
            int depth)          //深度
{
    hit_record rec;
    if(world->hit(r, 0.01, FLT_MAX, rec))
    {
        //rejection methodによって表面でランダム拡散
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation*color(scattered, world, depth+1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
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
    int object_num = 5; //物体数
    const char *filepath ="D:\\vsc\\c_cpp\\Raytracing\\chap.12_Defocus_Blur\\out_fov30deg_flesnelk_canceled.ppm";

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
        list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));          //lambertian..引数アルベド
        list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));     //床面の球
        list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));               //金属マテリアル  //fuzziness0.3...あまり散乱しない
        list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));              //ガラスマテリアル
        list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));              //中空ガラス表現するとき。負の半径いれてやると法線内向きのガラスを入れられる。

        hitable *world = new hitable_list(list, object_num);

        const auto aspect_ratio = double(ipix_size)/jpix_size;  //画像アス比
        vec3 lookfrom = vec3(-2, 2, 1);    //どこから見るか
        vec3 lookat = vec3(0, 0, -1);       //どこを見るか
        vec3 vup = vec3(0, 1, 0);           //ワールド座標の垂直ベクトル
        auto dist_to_focus = (lookat - lookfrom).length();     //lookatに焦点合わせている状態
        auto aperture = 2.0;

        camera cam(lookfrom, lookat, vup, 30, aspect_ratio, aperture, dist_to_focus);
        int progress_cnt = 0;
        for(int jpix = jpix_size - 1; jpix >= 0; jpix--)
        {
            for(int ipix = 0; ipix < ipix_size; ipix++)
            {
                vec3 col(0, 0, 0);
                //アンチエイリアスのために指定回数ランダムに光線をブレさせる
                for(int itr = 0; itr < itr_num; itr++)
                {
                    float u = float(ipix + random_double()) / float(ipix_size);      //水平方向の割合
                    float v = float(jpix + random_double()) / float(jpix_size);      //垂直方向の割合
                    ray r = cam.get_ray(u, v);
                    col += color(r, world, 0);
                }
                col /= float(itr_num);  //カラーは周辺の平均値
                col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));   //ガンマ補正
                
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);
                ofs << ir << " " << ig << " " << ib << "\n";

                printf("%d/%d: %lf\n",progress_cnt, ipix_size*jpix_size, double(progress_cnt)/double(ipix_size*jpix_size));
                progress_cnt++;
            }
        }
    }
}