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
