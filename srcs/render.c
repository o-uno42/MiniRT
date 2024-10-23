/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/10/22 19:25:22 by tjuvan           ###   ########.fr       */
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
// 	data->ambient.ratio = ft_atol(res[1]);
// 	rgb = safe_malloc(sizeof(int) * 4);
// 	rgb = ft_split(line, ',');
// 	data->ambient.rgb_1 = ft_atol(rgb[0]);
// 	data->ambient.rgb_2 = ft_atol(rgb[1]);
// 	data->ambient.rgb_3 = ft_atol(rgb[2]);
//     res = res;
// 	printf("AMBIENT\nRatio: %f\nrgb: %i\n%i\n%i\n\n", data->ambient.ratio, data->ambient.rgb_1, data->ambient.rgb_2, data->ambient.rgb_3);

// }


void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}


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


// static void	render_plane(int x, int y, t_data *data)
// {

// 	// float d = ((data->plane.vect.x * data->plane.posn.x) + (data->plane.vect.y * data->plane.posn.y)  + (data->plane.vect.z * data->plane.posn.z));
// 	float D = ((data->plane.vect.x * data->plane.posn.x) + (data->plane.vect.y * data->plane.posn.y)  + (data->plane.vect.z * data->plane.posn.z));
	
// 	float z = -(data->plane.pos.x * x + data->plane.pos.y * y + D) / data->plane.pos.z;
// 	// if (dot_product((sum_vect(data->plane.pos, data->plane.vect)), data->plane.posn) == 0)
// 	float result = data->plane.posn.x * x + data->plane.posn.y * y + data->plane.posn.y * z + D;
// 	if (result == 0 )
// 		my_pixel_put(data, x, y, BLUE);
	
// }

void	render_sphere(int x, int y, t_data *data)
{
	t_vect	ray_dir;
	t_vect	camera_pos;
	t_vect	offset_vect;
	float	aspect_ratio;
	float	ratio;
    int color;
    int color2;

	camera_pos = data->camera.pos;
	aspect_ratio = (float)data->img.width / (float)data->img.height;
    ratio = (float)x / (float)data->img.width;
    color = interpolate_color(CYAN, MAGENTA, ratio);
    color2 = interpolate_color(BLUE, BLACK, ratio);

	ray_dir.x = (2 * ((x + 0.5) / (float)data->img.width) - 1) * aspect_ratio;
    ray_dir.y = (1 - 2 * ((y + 0.5) / (float)data->img.height));
    ray_dir.z = -1;
    ray_dir = normalize(ray_dir);

	offset_vect = sub_vect(camera_pos, data->sphere.pos);

	float a = dot_product(ray_dir, ray_dir);
	float b = 2.0 * dot_product(offset_vect, ray_dir);
	float c = dot_product(offset_vect, offset_vect) - square(data->sphere.radius);
	float discriminant =  b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		float t = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t > 0)
		{
			my_pixel_put(data, x, y, color);
		}
	}
	else
        my_pixel_put(data, x, y, color2);
}

/* static void render_sphere(int x, int y, t_data *data) */ 
/* { */
/*     float ratio; */
/*     int color; */
/*     int color2; */
/* 	float d; */

/*     d = sqrt(square(x - (data->img.width / 2)) + square(y - (data->img.height / 2))); */

/*     ratio = (float)x / (float)data->img.width; */

/*     color = interpolate_color(CYAN, MAGENTA, ratio); */
/*     color2 = interpolate_color(BLUE, BLACK, ratio); */
/*     if (d <= data->sphere.radius) */
/* 	{ */
/*         my_pixel_put(data, x, y, color); */
/* 		// if (d == data->sphere.radius) */
/* 		// 	my_pixel_put(data, x, y, WHITE); */
/* 		// render_light(x, y, data); */
/* 	} */
/*     else */
/*         my_pixel_put(data, x, y, color2); */
/* } */

int    render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			render_sphere(x, y, data);
			/* render_plane(x, y, data); */
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}


