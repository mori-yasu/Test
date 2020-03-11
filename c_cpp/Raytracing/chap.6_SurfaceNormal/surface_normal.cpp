#include "ray.h"

//中心center, 半径radiusの球に対して、
float hit_sphere(const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0*dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0)
    {
        //その光線はヒットしない
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

//飛ばしたレイの色を取得する
vec3 color(const ray& r)
{
    //パラメータtの取得(ヒットしない場合は無効値として-1)
    float t = hit_sphere(vec3(0,0,-1), 0.5, r);
    if(t > 0.0)
    {
        //その光線の最終到達ポイントを球と判定
        //ヒットしている場合、その単位法線ベクトル = 光線ベクトルr - 原点ベクトルを計算する。
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
        //単位法線ベクトルの座標値をカラー値としてマッピング
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    else
    {
        //背景色をそのまま出す
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }    
}

int main()
{
    int nx = 2000;
    int ny = 1000;
    const char *filepath = "D:\\workspace\\vsc\\c_cpp\\Raytracing\\one_weekend\\chap.5_SurfaceNormal\\out.ppm";

    std::ofstream ofs(filepath);
    if(!ofs)
    {
        std::cout << "ファイルが開けませんでした。" << std::endl;
        std::cin.get();
        return 0;
    }
    else
    {
        //ピクセルサイズ
        int nx = 2000;   //pix
        int ny = 1000;   //pix
        //   std::cout << "P3\n" << nx << " " << ny << "\n255\n";
        ofs << "P3\n" << nx << " " << ny << "\n255\n";
        //↓スクリーン位置を表示するためのクラス(ピクセル座標ではなく実座標)
        vec3 lower_left_corner(-2.0, -1.0, -1.0);   //原点から見てスクリーン左下に向かうベクトル
        vec3 horizontal(4.0, 0.0, 0.0);             //スクリーン水平方向ベクトル
        vec3 vertical(0.0, 2.0, 0.0);               //スクリーン垂直方向のベクトル
        vec3 origin(0.0, 0.0, 0.0);                 //原点ベクトル

        for(int j = ny - 1; j >= 0; j--)
        {
            for(int i = 0; i < nx; i++)
            {
                //投影するスクリーン状の割合で表示する
                float u = float(i) / float(nx);
                float v = float(j) / float(ny);
                //今のピクセルに向かう光線rの定義。B…スクリーン左下から水平→垂直方向に進める。
                ray r(origin, lower_left_corner + u*horizontal + v*vertical);
                vec3 col = color(r);    //光線rのヒット先の色
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);
                ofs << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
}