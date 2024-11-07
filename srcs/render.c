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
// #include <climits>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

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
			
bool	render_sphere(t_ray camera_ray, t_data *data, int index)
{
	t_vect	offset_vect;
	float	intersect1;
	float	intersect2;


	offset_vect = sub_vect(data->camera.pos, data->obj[index].sphere->pos);

	float a = dot_product(camera_ray.dir, camera_ray.dir);
	float b = 2.0 * dot_product(camera_ray.dir, offset_vect);
	float c = dot_product(offset_vect, offset_vect) - square(data->obj[index].sphere->radius);
	if (solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0)
		{
			data->intersect->t0 = sum_vect(camera_ray.pos,scale_vector(camera_ray.dir, intersect1));
			return (true);
		}
	}
	return (false);
}


//formula : data->plane.vect.x * (camera_ray.dir.x - data->plane.pos.x) + data->plane.vect.y * (camera_ray.dir.y - data->plane.pos.y)  + data->plane.vect.z * (camera_ray.dir.z - data->plane.pos.z);
bool render_plane(t_ray camera_ray, t_data *data, int index_obj)
{
    float visibility;
	
	visibility = dot_product(data->obj[index_obj].plane->vect, camera_ray.dir);
    if (visibility <= 0)
        return (false);

    float D = -(dot_product(data->obj[index_obj].plane->vect, data->obj[index_obj].plane->pos));

    float t = -(D + dot_product(data->obj[index_obj].plane->vect, camera_ray.pos)) / visibility;

    return (t > 0);
}

t_plane		nearest_plane(t_data *data, t_ray camera_ray)
{
	int i;
	float distance;
	float	max;
	t_plane plane;

	i = 0;
	max = LONG_MAX;
	plane = data->obj->plane[i];
	while (i < data->index_objs)
	{
		distance = data->obj->plane[i].pos.z - camera_ray.pos.z;
		{
			if (distance < max)
				plane = data->obj->plane[i];
		}
		i++;
	}
	return (plane);
}

void swap_objs(t_objs *a, t_objs *b)
{
    t_objs tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}		

float get_object_distance(t_objs *obj, t_ray camera_ray)
{
    float dist;

    switch (obj->type_obj)
    {
        case SPHERE:
            dist = obj->sphere->pos.z - camera_ray.pos.z;
            break;
        case PLANE:
            dist = obj->plane->pos.z - camera_ray.pos.z;
            break;
        default:
            dist = INFINITY;
    }
    return (dist);
}

// t_sphere *sorted_spheres(t_data *data, t_ray camera_ray)
// {
//     int i;
// 	int j;
//     t_sphere *sphere;
// 	float dist1;
// 	float dist2;

// 	i = 0;
// 	j = 0;
//     sphere = safe_malloc(sizeof(t_sphere) * (data->obj->sphere->nb + 1));
//     while (i < data->obj->sphere->nb)
// 	{
//         sphere[i] = data->obj->sphere[i];
// 		i++;
// 	}
// 	i = 0;
//     while (i < data->obj->sphere->nb - 1)
//     {
// 		j = 0;
//         while (j < data->obj->sphere->nb - i - 1)
//         {
//             dist1 = sphere[j].pos.z - camera_ray.pos.z;
//             dist2 = sphere[j + 1].pos.z - camera_ray.pos.z;
            
//             if (dist1 < dist2)
//                 swap_spheres(&sphere[j], &sphere[j + 1]);
// 			j++;
//         }
// 		i++;
//     }
//     return (sphere);
// }
t_objs *sorted_objects(t_data *data, t_ray camera_ray)
{
    int i = 0;
    t_objs *objects;
    float dist1;
    float dist2;
	int j;

    objects = safe_malloc(sizeof(t_objs) * 1024);

    int num_objects = 0;
    while (data->obj[num_objects].type_obj != END)
	{
		num_objects++;
	}

	i = 0;
    while (i < num_objects)
	{
        objects[i] = data->obj[i];
		i++;
	}
    i = 0;
    while (i < num_objects - 1)
    {
		j = 0;
        while (j < num_objects - i - 1)
        {
            dist1 = get_object_distance(&objects[j], camera_ray);
            dist2 = get_object_distance(&objects[j + 1], camera_ray);

            if (dist1 < dist2)
                swap_objs(&objects[j], &objects[j + 1]);
			j++;
        }
		i++;
    }
    objects[num_objects].type_obj = END;
    
    return (objects);
}

void	render_obj(t_data *data, t_ray camera_ray, int type, int x, int y, int index_obj, t_ray *light)
{
	int		color;
	// t_vect	reflection_vect;

		// printf("Generic :%i\n", type);
	if (type == 1)
	{
		// printf("RENDER SPHERE\n");
		// printf("%i", type);
		color = create_color(data->obj[index_obj].sphere->rgb, data->ambient);
		if(render_sphere(camera_ray, data, index_obj))
		{
			// my_pixel_put(data, x, y, light_intersect(data, light, camera_ray, index_obj));
			if(!light_intersect(data, light, camera_ray, index_obj))
				my_pixel_put(data, x, y, WHITE);
			// else if (light_intersect(data, light, camera_ray, index_obj) == 3)
			// 	my_pixel_put(data, x, y, BLACK);
			else
				my_pixel_put(data, x, y, color);
			
			// reflection_vect = specular_light_sphere(data, light, camera_ray, index_obj);

			// if (reflection_intersect(data, reflection_vect, camera_ray, index_obj))
			// 	my_pixel_put(data, x, y, RED);
			
		}
	}
	else if (type == 2)
	{
		color = create_color(data->obj[index_obj].plane->rgb, data->ambient);
		if(render_plane(camera_ray, data, index_obj))
			my_pixel_put(data, x, y, color);
	}
}

void	render_objs(t_data *data, t_ray camera_ray, int x, int y, t_ray *light)
{
	int i = 0;
	int index_obj = 0;

	i = 0;
	while (data->obj[i].type_obj != END)
	{
		// printf("TYPE : %i", data->obj[i].type_obj);
		// printf("rendering\n");
		render_obj(data, camera_ray, data->obj[i].type_obj, x, y, index_obj, light);
		i++;
		index_obj++;
	}
}


int    render(t_data *data)
{
	int	x;
	int	y;
	// int z;
	t_ray camera_ray;
	t_ray *light;
	t_objs	*sorted;

	int i = -1;
	while(i++ < 50)
		printf("type render: %i\n", data->obj[i].type_obj);

	data->img_ratio = ratio(data->img.width, data->img.height);
	print_camera(data->camera);
	// sorted = safe_malloc(sizeof(t_objs) * 1024);
	sorted = sorted_objects(data, camera_ray);
	data->obj = sorted;
	// print_sphere(data->sphere);

	light = light_rays(data);
	light = light;
	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			camera_ray = camera_rays(x, y,data);
			render_objs(data, camera_ray, x, y, light);
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

