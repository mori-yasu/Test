#include "ray.h"

vec3 color(const ray& r)
{
    //単位ベクトルを作成
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    
}

int main()
{
    int nx = 200;
    int ny = 100;
    const char *filepath = "D:\\workspace\\vsc\\c_cpp\\Raytracing\\one_weekend\\chap.1\\out.png";

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
        ofs << "P3\n" << nx << " " << ny << "\n255\n";
        for(int j = ny - 1; j >= 0; j--)
        {
            for(int i = 0; i < nx; i++)
            {
                float r = float(i) / float(nx);
                float g = float(j) / float(ny);
                float b = 0.2;
                int ir = int(255.99*r);
                int ig = int(255.99*g);
                int ib = int(255.99*b);
                ofs << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
}