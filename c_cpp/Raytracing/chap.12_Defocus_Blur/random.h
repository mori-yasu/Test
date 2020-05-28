#ifndef _RANDOM_H
#define _RANDOM_H

#include <cstdlib>
#include "hitable.h"
#include "MT.h"

//ランダムな-1～1の乱数を生成する
inline double random_double()
{

    return 2.0*genrand_real3() - 1.0;
}


#endif