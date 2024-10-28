/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/10/28 17:20:32 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}

bool solve_quadratic(const float a, const float b, const float c, float *x0, float *x1)
{
	float	discr;
	float	q;

	discr = b * b -4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
	{
		*x0 = -0.5 * b / a;
		*x1 = *x0;
	}
	else
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discr));
		else
			q = -0.5 * (b - sqrt(discr));
		*x0 = q / a;
		*x1 = c / q;
	}
	if (*x0 > *x1)
		swap(x0, x1);
	return (true);
}
			
bool	render_sphere(t_ray camera_ray, t_data *data)
{
	t_vect	offset_vect;
	float	intersect1;
	float	intersect2;

	offset_vect = sub_vect(data->camera.pos, data->sphere.pos);

	float a = dot_product(camera_ray.dir, camera_ray.dir);
	float b = 2.0 * dot_product(camera_ray.dir, offset_vect);
	float c = dot_product(offset_vect, offset_vect) - square(data->sphere.radius);
	if (solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0)
			return (true);
	}
	return (false);
}

int    render(t_data *data)
{
	int	x;
	int	y;
	// int z;
	t_ray camera_ray;

	data->img_ratio = ratio(data->img.width, data->img.height);
	print_camera(data->camera);
	print_sphere(data->sphere);

	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			camera_ray = camera_rays(x, y,data);
			if (x == data->img.width /2)
				print_ray(camera_ray);
			// render_scene(camera_ray, data);
			if(render_sphere(camera_ray,  data))
				my_pixel_put(data, x, y, RED);
			/* render_plane(x, y, data); */
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}

/* static int render_sphere(t_ray camera_ray, t_data *data) */
/* { */
/*     // float ratio; */
/*     // int color; */
/*     // int color2; */
/*     float d; */
/* 	// t_vect coords; */
/* 	// int z = data->sphere.pos.z; */
	
/* 	// coords = camera_rays(x, y, z, data); */
/* 	d = sqrt(square (camera_ray.dir.x - data->sphere.pos.x) + square(camera_ray.dir.y - data->sphere.pos.y)); */

/*     // ratio = (float)x / (float)data->img.width; */

/*     // color = interpolate_color(CYAN, MAGENTA, ratio); */
/*     // color2 = interpolate_color(BLUE, BLACK, ratio); */
/*     if (d <= data->sphere.radius * data->sphere.pos.z) */
/* 	{ */
/* 		if ((camera_ray.dir.x <= data->img.width) && (camera_ray.dir.y <= data->img.height)) */
/* 		{ */

/* 			return( 1); */
/* 			// render_light(camera_ray.x, camera_ray.y, z, data); */

/* 			// if (render_light(x, y, data)) */
/* 			// 	my_pixel_put(data, coords.x, coords.y, WHITE); */
/* 			// else */
/* 			// 	my_pixel_put(data, coords.x, coords.y, GREEN); */
/* 		} */
/* 		// if (render_light(x, y, data) && (coords.x <= data->img.width) && (coords.y <= data->img.height)) */
/*         // 	my_pixel_put(data, coords.x, coords.y, WHITE); */
/* 		// else if (!render_light(x, y, data) && (coords.x <= data->img.width) && (coords.y <= data->img.height)) */
/* 		// 	my_pixel_put(data, coords.x, coords.y, GREEN); */
/* 	} */
/* 	return 0; */
/*     // else */
/* 	// 	if ((x + data->camera.pos.x <= data->img.width) && (y + data->camera.pos.y <= data->img.height)) */
/* 	// 	my_pixel_put(data, x+ data->camera.pos.x, y + data->camera.pos.y, BLUE ); */
/* } */

// void	render_scene(int x, int y, t_data *data)
// {
// 	render_sphere(x, y, data);
// }

// static int render_light(int x, int y, int z, t_data *data)
// {
// 	// int d = 0;
// 	z = z;
// 	x = x;
// 	y = y;
// 	// while (i <= data->light.bright)
// 	// {
// 	// 	if (i == data->sphere.radius)
// 	// 		my_pixel_put(data, x, y, WHITE);
// 	// 	i++;
// 	// }
// 	// d = sqrt(square(x - data->sphere.pos.x) + square(y - data->sphere.pos.y));
// 	// if (d <= data->sphere.radius * data->sphere.pos.z / 4)
// 	// 	return (1);
// 	// else
// 	//  	return 0;;
// 	// t_vect vector;
// 	float	len_vect;
	
// 	// vector = vector;
// 	len_vect = sqrt(square(data->light.pos.x) +square(data->light.pos.y)+square(data->light.pos.z));

// 	printf ("len vect light:%f\n", len_vect);
// 	return  (1);
// 	// while ()
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

