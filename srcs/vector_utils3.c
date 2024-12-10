#include "../includes/minirt.h"
#include <math.h>

t_vect    abs_vect(t_vect vect)
{
    vect.x = fabs(vect.x);
    vect.y = fabs(vect.y);
    vect.z = fabs(vect.z);
    return (vect);
}