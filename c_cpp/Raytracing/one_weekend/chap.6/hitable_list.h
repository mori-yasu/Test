#ifndef _HITABLE_LIST_H
#define _HITABLE_LIST_H

#include "hitable.h"

class hitable_list: public hitable
{
    public:
        hitable_list(){}
        hitable_list(hitable **l, int n)
        {
            list = l;
            list_size = n;
        }
        virtual bool hit(   const ray& r,       //入射光線
                            float t_min,
                            float t_max,
                            hit_record& rec) const;
        hitable **list;
        int list_size;
};

bool hitable_list::hit( const ray& r,       //入射光線
                        float t_min,
                        float t_max,
                        hit_record& rec)const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;      //これまでで最も近いt
    for(int i = 0; i < this->list_size; i++)
    {
        //最も近いtを更新し続ける
        if(this->list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif