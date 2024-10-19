/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/10/19 20:59:10 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

// void    ambient_init(t_data *data, char *line)
// {
//     int     i;
// 	int		j;
//     char    **res;
// 	char	**rgb;

//     i = 0;
//     i= i;
// 	j =0;
// 	j = j;
// 	rgb = NULL;
// 	rgb = rgb;
//     data = data;
//     res = NULL;
//     line = line;
//     res = safe_malloc(sizeof(char *) * 3); 
//     // res = ft_split_rt(line, ',');
// 	res = ft_split(line, ' ');
// 	// printf ("res 1 %s\n", res[0]);
// 	// printf ("res 1 %s\n", res[1]);
// 	// while (res[j])
// 	// 	j++;
// 	// if (j != 1)
// 	// 	print_error("Wrong parameters for Ambient Light");
// 	data->ambient.ratio = ft_atoi(res[1]);
// 	rgb = safe_malloc(sizeof(int) * 4);
// 	rgb = ft_split(line, ',');
// 	data->ambient.rgb_1 = ft_atoi(rgb[0]);
// 	data->ambient.rgb_2 = ft_atoi(rgb[1]);
// 	data->ambient.rgb_3 = ft_atoi(rgb[2]);
//     res = res;
// 	printf("AMBIENT\nRatio: %f\nrgb: %i\n%i\n%i\n\n", data->ambient.ratio, data->ambient.rgb_1, data->ambient.rgb_2, data->ambient.rgb_3);

// }

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

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}

int	square(int i)
{
	return (i * i);
}

// static void	render_scene(int x, int y, t_data *data)
// {
// 	float	ratio;
// 	int		color;
// 	int		color2;
// 	int		d;

// 	d = sqrt(square(x - (data->img.width / 2)) + square(y - (data->img.height / 2)));
// 	ratio = (float)x / (float)data->img.width;
// 	color = interpolate_color(BLACK, MAGENTA, ratio);
// 	color2 = interpolate_color(YELLOW, BLACK, ratio);
// 	if (d > data->img.width / 4)
// 		my_pixel_put(data, x, y, color);
// 	else
// 		my_pixel_put(data, x, y, color2);

// }

// static void render_light(int x, int y, t_data *data)
// {
// 	int i = 0;
// 	while (i <= data->light.bright)
// 	{
// 		if (i == data->sphere.radius)
// 			my_pixel_put(data, x, y, WHITE);
// 		i++;
// 	}

// }

static t_vect sum_vect(t_vect pos_1, t_vect pos_2)
{
    t_vect res;
    res.x = pos_1.x + pos_2.x;
    res.y = pos_1.y + pos_2.y;
    res.z = pos_1.z + pos_2.z;

    return (res);
}

static float	dot_product(t_vect pos_1, t_vect pos_2)
{
	return ((pos_1.x * pos_2.x) + (pos_1.y * pos_2.y) + (pos_1.z * pos_2.z));
}

static void	render_plane(int x, int y, t_data *data)
{
	int color;
	int i = 0;
	float ratio;
	ratio = (float)x / (float)data->img.width;
	color = interpolate_color(RED, RED, ratio);

	while (i < dot_product((sum_vect(data->plane.pos, data->plane.vect)), data->plane.posn))
	{
		if (dot_product((sum_vect(data->plane.pos, data->plane.vect)), data->plane.posn) == 0)
			my_pixel_put(data, x, y, color);
		i++;
	}
	// while (i < dot_product(data->plane.pos, data->plane.posn))
	// {
	// 	my_pixel_put(data, x, y, color);
	// 	i++;
	// }

	
}

static void render_sphere(int x, int y, t_data *data) 
{
    float ratio;
    int color;
    int color2;
	float d;

    d = sqrt(square(x - (data->img.width / 2)) + square(y - (data->img.height / 2)));

    ratio = (float)x / (float)data->img.width;

    color = interpolate_color(CYAN, MAGENTA, ratio);
    color2 = interpolate_color(BLUE, BLACK, ratio);
    if (d <= data->sphere.radius)
	{
        my_pixel_put(data, x, y, color);
		// if (d == data->sphere.radius)
		// 	my_pixel_put(data, x, y, WHITE);
		// render_light(x, y, data);
	}
    else
        my_pixel_put(data, x, y, color2);
}


// void	render_sphere(t_data *data)
// {
	
// }

int    render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->img.height)
	{
		x = 0;
		while (x <= data->img.width)
		{
			render_sphere(x, y, data);
			render_plane(x, y, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}

void	plane_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**vect;
	char	**rgb;

	res = safe_malloc(sizeof(char *) * 4);
	res = ft_split(line, ' ');

	coords =safe_malloc(sizeof(char *) * 4);
	coords = ft_split(res[1], ',');
	data->plane.pos.x = ft_atoi(coords[0]);
	data->plane.pos.y = ft_atoi(coords[1]);
	data->plane.pos.z = ft_atoi(coords[2]);

	// printf("%f", data->plane.pos.z);

	data->plane.posn.x = data->plane.pos.x;
	data->plane.posn.y = data->plane.pos.y + 10;
	data->plane.posn.z = data->plane.pos.z;

	vect = safe_malloc(sizeof(char *) * 4);
	vect = ft_split(res[2],  ',');
	data->plane.vect.x = ft_atoi(vect[0]);
	data->plane.vect.y = ft_atoi(vect[1]);
	data->plane.vect.z = ft_atoi(vect[2]);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->plane.rgb.r = ft_atoi(rgb[0]);
	data->plane.rgb.g = ft_atoi(rgb[1]);
	data->plane.rgb.b = ft_atoi(rgb[2]);
}

void	sphere_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**rgb;

	res = safe_malloc(sizeof(char *) * 4);
	res = ft_split(line, ' ');

	coords =safe_malloc(sizeof(char *) * 4);
	coords = ft_split(res[1], ',');
	data->sphere.pos.x = ft_atoi(coords[0]);
	data->sphere.pos.y = ft_atoi(coords[1]);
	data->sphere.pos.z = ft_atoi(coords[2]);

	data->sphere.diameter = ft_atoi(res[2]);
	data->sphere.radius = (data->sphere.diameter/2);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->sphere.rgb.r = ft_atoi(rgb[0]);
	data->sphere.rgb.g = ft_atoi(rgb[1]);
	data->sphere.rgb.b = ft_atoi(rgb[2]);
}

void    ambient_init(t_data *data, char *line)
{
    int     i;
	int		j;
    char    **res;
	char	**rgb;

    i = 0;
    i= i;
	j =0;
	j = j;
	rgb = NULL;
	rgb = rgb;
    data = data;
    res = NULL;
    line = line;
    res = safe_malloc(sizeof(char *) * 3); 
    // res = ft_split_rt(line, ',');
	res = ft_split(line, ' ');
	// printf ("res 1 %s\n", res[0]);
	// printf ("res 1 %s\n", res[1]);
	// while (res[j])
	// 	j++;
	// if (j != 1)
	// 	print_error("Wrong parameters for Ambient Light");
	data->ambient.ratio = ft_atoi(res[1]);
	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(line, ',');
	data->ambient.rgb.r = ft_atoi(rgb[0]);
	data->ambient.rgb.g = ft_atoi(rgb[1]);
	data->ambient.rgb.b = ft_atoi(rgb[2]);
    res = res;
	// printf("AMBIENT\nRatio: %f\nrgb: %i\n%i\n%i\n\n", data->ambient.ratio, data->ambient.rgb_1, data->ambient.rgb_2, data->ambient.rgb_3);

}

void	camera_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**vector;

	res = safe_malloc(sizeof(float) * 4);
	res = ft_split(line, ' ');

	coords = safe_malloc(sizeof(float) * 4);
	coords = ft_split(res[2], ',');
	data->camera.pos.x = ft_atoi(coords[0]);
	data->camera.pos.y = ft_atoi(coords[1]);
	data->camera.pos.z = ft_atoi(coords[2]);

	vector = safe_malloc(sizeof(float) * 4);
	vector = ft_split(res[3], ',');
	data->camera.vx = ft_atoi(vector[0]);
	// data->camera.vy = ft_atoi(vector[1]);
	// data->camera.vz = ft_atoi(vector[2]);

	data->camera.fov = ft_atoi(res[4]);
	// printf ("CAMERA\nx: %f\ny: %f\nz: %f\nvx: %f\nvy: %f\nvz: %f\n\n", 
	// 	data->camera.x, data->camera.y, data->camera.z, data->camera.vx, data->camera.vy, data->camera.vz);
}

void	light_init(t_data *data, char *line)
{
	char **res;
	char **coords;
	char **rgb;

	res = safe_malloc(sizeof(float) * 4);
	res = ft_split(line, ' ');

	coords = safe_malloc(sizeof(float) * 4);
	coords = ft_split(res[1], ',');

	data->light.pos.x = ft_atoi(coords[0]);
	data->light.pos.y = ft_atoi(coords[1]);
	data->light.pos.z = ft_atoi(coords[2]);

	data->light.bright = ft_atoi(res[2]);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->light.rgb.r = ft_atoi(rgb[0]);
	data->light.rgb.g = ft_atoi(rgb[1]);
	data->light.rgb.b = ft_atoi(rgb[2]);
	// printf("LIGHT\nCoords: %f\n%f\n%f\nBright: %f\nRgb: %i\n%i\n%i\n\n", 
	// 	data->light.x, data->light.y, data->light.z, data->light.bright,
	// 		data->light.rgb_1, data->light.rgb_2, data->light.rgb_3);
}

// void	my_pixel_put(t_data *data, int x, int y, int color)
// {
// 	int		offset;
// 	char	*dest;

// 	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
// 	dest = data->img.pix_ptr + offset;
// 	*(unsigned int *)dest = color;
// }


// static void	render_scene(int x, int y, t_data *data)
// {
// 	my_pixel_put(data, x, y, MAGENTA);
// }

// int    render(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y <= data->img.height)
// 	{
// 		x = 0;
// 		while (x <= data->img.width)
// 		{
// 			render_scene(x, y, data);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, 
// 		data->img.img_ptr, 0, 0);
// 	return (0);
// }

// a = PI *r^2
