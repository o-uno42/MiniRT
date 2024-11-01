#include "../includes/minirt.h"


int     create_color(t_rgb rgb, t_ambient ambient)
{
    int r;
    int g;
    int b;

    r = (rgb.r + ambient.rgb.r) * ambient.ratio;
    g = (rgb.g + ambient.rgb.g) * ambient.ratio;
    b = (rgb.b + ambient.rgb.b) * ambient.ratio;
    return ((r << 16) | (g << 8) | b);
}