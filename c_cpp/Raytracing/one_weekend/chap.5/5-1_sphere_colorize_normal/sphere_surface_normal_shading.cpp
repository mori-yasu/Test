#include "../../integrated/header/ray.h"

//t*t*dot(B, B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0の二次方程式の解
float hit_sphere(const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;                  //A - C
    float a = dot(r.direction(), r.direction());    //dot(B, B)
    float b = 2.0 * dot(oc, r.direction());         //2.0*dot(B,A-C)
    float c = dot(oc, oc) - radius * radius;        //dot(A-C,A-C) - R*R
    float discriminant = b*b - 4.0 * a * c;
    if(discriminant < 0)    //rが球に触れていない
    {
        return -1.0;
    }
    //球表面にあるパラメータtを返す
    else{
        return (-b - sqrt(discriminant)) / (2.0*a); //球表面にヒットするパラメータt(ヒットポイントの近い側。小さい方のt)
    }

}

vec3 color(const ray& r)    //input: r⇒スクリーン上の1pixに向かうベクトル
{
    //draw sphere
    float t = hit_sphere(vec3(0, 0, -1), 0.5, r);   //スクリーン原点で0.5半径の球とrベクトルの設置判定
    //ヒット判定でカラーを変える
    if(t > 0.0) //ベクトルrが球面を通っている()
    {
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));     //rヒットポイントの法線単位ベクトル
        return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);                   //x/y/z(-1 ~ 1) ⇒ r/g/b(0 ~ 1)
    }    

    //draw background
    vec3 unit_direction = unit_vector(r.direction());                   //単位ベクトルを作成
    t = 0.5*(unit_direction.y() + 1.0);                           //パラメータtの作成(0～1)
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);       //白(1.0, 1.0, 1.0)と青(0.5, 0.7, 1.0)をどれだけの割合でブレンドするか
    
}

int main()
{
    int ipix_size = 2000;
    int jpix_size = 1000;
    const char *filepath ="D:\\vsc\\c_cpp\\Raytracing\\one_weekend\\chap.5\\out_sphere_normal_map_fine.ppm";

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
        
        for(int jpix = jpix_size - 1; jpix >= 0; jpix--)
        {
            for(int ipix = 0; ipix < ipix_size; ipix++)
            {
                //パラメータ(ex.p(t) = A + t*Bのt)
                float u = float(ipix) / float(ipix_size);                       //水平方向のパラメータ
                float v = float(jpix) / float(jpix_size);                       //垂直方向のパラメータ       
                ray r(origin, lower_left_corner + u*horizontal + v*vertical);    //カメラからスクリーン上の各ピクセルに飛ばした光線ベクトル
                
                vec3 col = color(r);        //カラーの取得[r_normal,g_normal,b_normal](0 ~ 1) 
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);
                
                ofs << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
}