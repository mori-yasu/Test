#include "ray.h"

vec3 color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main()
{
    const char *filepath = "D:\\workspace\\vsc\\c_cpp\\Raytracing\\one_weekend\\chap.3_Ray,camera\\out.ppm";

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
        int nx = 200;   //pix
        int ny = 100;   //pix
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

    ofs.close();
}