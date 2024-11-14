#include "../includes/minirt.h"



t_rgb     create_color_rgb(t_rgb rgb, t_ambient ambient)
{
    t_rgb res;

    res.r = (rgb.r + ambient.rgb.r) * ambient.ratio;
    res.g = (rgb.g + ambient.rgb.g) * ambient.ratio;
    res.b = (rgb.b + ambient.rgb.b) * ambient.ratio;
    return (res);
}


int     create_color_int(t_rgb rgb)
{
    int r;
    int g;
    int b;

    r = (rgb.r);
    g = (rgb.g);
    b = (rgb.b);
    return ((r << 16) | (g << 8) | b);
}

t_ambient   darker_ambient(t_ambient ambient, float i)
{
    t_ambient res;

    res.rgb.r = ambient.rgb.r / i;
    res.rgb.g = ambient.rgb.g / i;
    res.rgb.b = ambient.rgb.b / i;

    if (res.rgb.r < 0)
        res.rgb.r = 0;
    if (res.rgb.g < 0)
        res.rgb.g = 0;
    if (res.rgb.b < 0)
        res.rgb.b = 0;
    return (res);
}

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

int just_color(t_rgb rgb)
{
    int r;
    int g;
    int b;

    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
    return ((r << 16) | (g << 8) | b);
}

t_rgb	extract_color(int r, int g, int b)
{
	t_rgb	color;

	color.b = b;
	color.g = g;
	color.r = r;
	return (color);
}

t_rgb	extract_color_from_int(int color)
{
	t_rgb	rgb;
	
	rgb.r = get_r(color);
	rgb.g = get_g(color);
	rgb.b = get_b(color);
	return (rgb);
}

t_vect	rgb_to_vect(t_rgb color)
{
	t_vect	v;

	v.x = color.r;
	v.y = color.g;
	v.z = color.b;
	return (v);
}

int	interpolate_color(int color1, int color2, float ratio)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = (int)(get_t(color1) * (1 - ratio) + get_t(color2) * ratio);
	r = (int)(get_r(color1) * (1 - ratio) + get_r(color2) * ratio);
	g = (int)(get_g(color1) * (1 - ratio) + get_g(color2) * ratio);
	b = (int)(get_b(color1) * (1 - ratio) + get_b(color2) * ratio);
	return (create_trgb(t, r, g, b));
}
