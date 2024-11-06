/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:32:06 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/06 19:00:56 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_hitinfo	init_hit(t_data *data)
{
	t_hitinfo	hit;

	hit.p = create_vector(0, 0, 0);
	hit.t = FLT_MAX;
	hit.normal = create_vector(0, 0 , 0);
	hit.rgb = data->ambient.rgb;
	return (hit);
}
void	plane_init(t_data *data, char *line, int i)
{
	char	**res;
	char	**coords;
	char	**vect;
	char	**rgb;
	t_plane	*plane;

	data->obj[i].type_obj = PLANE;
	plane = (t_plane *)safe_malloc(sizeof(t_plane));
	data->obj[i].object = plane;
	res = ft_split(line, ' ');

	coords = ft_split(res[1], ',');
	plane->pos.x = ft_atol(coords[0]);
	plane->pos.y = ft_atol(coords[1]);
	plane->pos.z = ft_atol(coords[2]);

	plane->posn.x = plane->pos.x;
	plane->posn.y = plane->pos.y + 10;
	plane->posn.z = plane->pos.z;

	vect = ft_split(res[2],  ',');
	plane->vect.x = ft_atol(vect[0]);
	plane->vect.y = ft_atol(vect[1]);
	plane->vect.z = ft_atol(vect[2]);

	rgb = ft_split(res[3], ',');
	plane->rgb.r = ft_atol(rgb[0]);
	plane->rgb.g = ft_atol(rgb[1]);
	plane->rgb.b = ft_atol(rgb[2]);
	free_mtx(rgb);
	free_mtx(vect);
	free_mtx(coords);
	free_mtx(res);

}

void	sphere_init(t_data *data, char *line, int i)
{
	char	**res;
	char	**coords;
	char	**rgb;
	t_sphere	*sphere;

	data->obj[i].type_obj = SPHERE;
	sphere = (t_sphere *)safe_malloc(sizeof(t_sphere));
	data->obj[i].object = sphere;
	res = ft_split(line, ' ');

	coords = ft_split(res[1], ',');
	sphere->pos.x = ft_atol(coords[0]);
	sphere->pos.y = ft_atol(coords[1]);
	sphere->pos.z = ft_atol(coords[2]);

	sphere->diameter = ft_atol(res[2]);
	sphere->radius = sphere->diameter / 2;

	rgb = ft_split(res[3], ',');
	sphere->rgb.r = ft_atol(rgb[0]);
	sphere->rgb.g = ft_atol(rgb[1]);
	sphere->rgb.b = ft_atol(rgb[2]);
	free_mtx(rgb);
	free_mtx(coords);
	free_mtx(res);
}

void	top_bottom_point(POINT *p1, POINT *p2, t_cylinder cylinder)
{
	*p1 = sum_vect(cylinder.pos, scale_vect(cylinder.dir, cylinder.height / 2));
	*p2 = sum_vect(cylinder.pos, scale_vect(cylinder.dir, (- cylinder.height) / 2));
}

void	cylinder_init(t_data *data, char *line, int i)
{
	char		**res;
	char		**coords;
	t_cylinder	*cylinder;
	POINT		p1;
	POINT		p2;

	data->obj[i].type_obj = CYLINDER;
	cylinder = (t_cylinder *)safe_malloc(sizeof(t_cylinder)); 
	data->obj[i].object = cylinder;
	res = ft_split(line, ' ');

	coords = ft_split(res[1], ',');
	cylinder->pos.x = ft_atol(coords[0]);
	cylinder->pos.y = ft_atol(coords[1]);
	cylinder->pos.z = ft_atol(coords[2]);
	free_mtx(coords);

	coords = ft_split(res[2], ',');
	cylinder->dir.x = ft_atol(coords[0]);
	cylinder->dir.y = ft_atol(coords[1]);
	cylinder->dir.z = ft_atol(coords[2]);
	cylinder->dir = normalize(cylinder->dir);
	free_mtx(coords);

	cylinder->diameter = ft_atol(res[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atol(res[4]);

	coords = ft_split(res[3], ',');
	cylinder->rgb.r = ft_atol(coords[0]);
	cylinder->rgb.g = ft_atol(coords[1]);
	cylinder->rgb.b = ft_atol(coords[2]);
	top_bottom_point(&p1, &p2, *cylinder);
	cylinder->p1 = p1;
	cylinder->p2 = p2;
	free_mtx(coords);
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
	data->ambient.ratio = ft_atol(res[1]);
	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(line, ',');
	data->ambient.rgb.r = ft_atol(rgb[0]);
	data->ambient.rgb.g = ft_atol(rgb[1]);
	data->ambient.rgb.b = ft_atol(rgb[2]);
    res = res;
	// printf("AMBIENT\nRatio: %f\nrgb: %i\n%i\n%i\n\n", data->ambient.ratio, data->ambient.rgb_1, data->ambient.rgb_2, data->ambient.rgb_3);

}

void	camera_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**vector;
	t_vect	world_up;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	res = safe_malloc(sizeof(float) * 4); // IS this alloc necessary if later we use split???
	res = ft_split(line, ' ');

	coords = safe_malloc(sizeof(float) * 4);
	coords = ft_split(res[1], ',');
	data->camera.pos.x = ft_atol(coords[0]);
	data->camera.pos.y = ft_atol(coords[1]);
	data->camera.pos.z = ft_atol(coords[2]);

	vector = safe_malloc(sizeof(float) * 4);
	vector = ft_split(res[2], ',');
	data->camera.dir.x = ft_atol(vector[0]);
	// data->camera.dir.x = (ft_atol(vector[0]));
	data->camera.dir.y = ft_atol(vector[1]);
	data->camera.dir.z = ft_atol(vector[2]);
	// data->camera.vy = ft_atol(vector[1]);
	// data->camera.vz = ft_atol(vector[2]);

	data->camera.fov = ft_atoi(res[3]);
	data->camera.forward = normalize(data->camera.dir);// normalize(sub_vect(data->camera.dir, data->camera.pos));
	if (data->camera.dir.x == 0 && data->camera.dir.z == 0)
	{
		data->camera.right = create_vector(1.0, 0, 0);
		data->camera.up = create_vector(0, 0, 1.0);
	}
	else
	{
		data->camera.right = normalize(cross_product(world_up, data->camera.forward));
		data->camera.up = cross_product(data->camera.forward, data->camera.right);
	}
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

	data->light.pos.x = ft_atol(coords[0]);
	data->light.pos.y = ft_atol(coords[1]);
	data->light.pos.z = ft_atol(coords[2]);

	data->light.bright = ft_atol(res[2]);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->light.rgb.r = ft_atol(rgb[0]);
	data->light.rgb.g = ft_atol(rgb[1]);
	data->light.rgb.b = ft_atol(rgb[2]);
	// printf("LIGHT\nCoords: %f\n%f\n%f\nBright: %f\nRgb: %i\n%i\n%i\n\n", 
	// 	data->light.x, data->light.y, data->light.z, data->light.bright,
	// 		data->light.rgb_1, data->light.rgb_2, data->light.rgb_3);
}
