/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:32:06 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/17 15:41:06 by tjuvan           ###   ########.fr       */
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
	// plane->vect = normalize(plane->vect);

	rgb = ft_split(res[3], ',');
	plane->rgb.r = ft_atol(rgb[0]);
	plane->rgb.g = ft_atol(rgb[1]);
	plane->rgb.b = ft_atol(rgb[2]);
	if (res[4] && (ft_atoi(res[4]) == 0 || ft_atoi(res[4]) == 1))
	{
		plane->checker = ft_atoi(res[4]);
		plane->bonus = ft_atoi(res[4]);
	}
	else
	{
		plane->checker = false;
		plane->bonus = false;
	}
	if (res[5])
		plane->tex = data->pics[ft_atoi(res[5])];
	if (res[6])
		plane->tex_norm = data->pics[ft_atoi(res[6])];


	free_mtx(rgb);
	free_mtx(vect);
	free_mtx(coords);
	free_mtx(res);

}

void	top_bottom_cone(POINT *p1, POINT *p2, t_cone cone)
{
	*p1 = sum_vect(cone.pos, scale_vect(cone.dir, cone.height / 2));
	*p2 = sum_vect(cone.pos, scale_vect(cone.dir, - cone.height / 2));
}

void	cone_angle(t_cone *cone)
{
	float	angle;
	angle = atan2((*cone).radius, (*cone).height / 2);
	(*cone).theta_r = angle;
	(*cone).theta_d = angle * (180 / M_PI);
}

void	cone_init(t_data *data, char *line, int i)
{
	char		**res;
	char		**coords;
	t_cone		*cone;
	POINT		p1;
	POINT		p2;

	data->obj[i].type_obj = CONE;
	cone = (t_cone *)safe_malloc(sizeof(t_cone)); 
	data->obj[i].object = cone;
	res = ft_split(line, ' ');

	coords = ft_split(res[1], ',');
	cone->pos = create_vector(ft_atol(coords[0]),ft_atol(coords[1]),ft_atol(coords[2]));
	free_mtx(coords);

	coords = ft_split(res[2], ',');
	cone->dir = create_vector(ft_atol(coords[0]),ft_atol(coords[1]),ft_atol(coords[2]));
	cone->dir = normalize(cone->dir);
	free_mtx(coords);

	cone->diameter = ft_atol(res[3]);
	cone->radius = cone->diameter / 2.0;
	cone->height = ft_atol(res[4]);
	cone_angle(cone);
	top_bottom_cone(&p1, &p2, *cone); 
	cone->p1 = p1;
	cone->p2 = p2;

	coords = ft_split(res[5], ',');
	cone->rgb.r = ft_atol(coords[0]);
	cone->rgb.g = ft_atol(coords[1]);
	cone->rgb.b = ft_atol(coords[2]);
	if (res[6] && (ft_atoi(res[6]) == 0 || ft_atoi(res[6]) == 1))
	{
		cone->checker = ft_atoi(res[6]);
		cone->bonus = ft_atoi(res[6]);
	}
	else
	{
		cone->checker = false;
		cone->bonus = false;
	}
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
	if (res[4] && (ft_atoi(res[4]) == 0 || ft_atoi(res[4]) == 1))
	{
		sphere->checker = ft_atoi(res[4]);
		sphere->bonus = ft_atoi(res[4]);
	}
	else
	{	
		sphere->checker = false;
		sphere->bonus = false;
	}
	if (res[5])
		sphere->tex = data->pics[ft_atoi(res[5])];
	if (res[6])
		sphere->tex_normal = data->pics[ft_atoi(res[6])];
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

	coords = ft_split(res[2], ',');
	cylinder->dir.x = ft_atol(coords[0]);
	cylinder->dir.y = ft_atol(coords[1]);
	cylinder->dir.z = ft_atol(coords[2]);
	cylinder->dir = normalize(cylinder->dir);
	free_mtx(coords);

	cylinder->diameter = ft_atol(res[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atol(res[4]);

	coords = ft_split(res[5], ',');
	cylinder->rgb.r = ft_atol(coords[0]);
	cylinder->rgb.g = ft_atol(coords[1]);
	cylinder->rgb.b = ft_atol(coords[2]);
	top_bottom_point(&p1, &p2, *cylinder);
	cylinder->p1 = p1;
	cylinder->p2 = p2;
	if (res[6] && (ft_atoi(res[6]) == 0 || ft_atoi(res[6]) == 1))
	{
		cylinder->checker = ft_atoi(res[6]);
		cylinder->bonus = ft_atoi(res[6]);
	}
	else
	{
		cylinder->checker = false;
		cylinder->bonus = false;
	}
	if (res[7])
		cylinder->tex = data->pics[ft_atoi(res[7])];
	if (res[8])
		cylinder->tex_normal = data->pics[ft_atoi(res[8])];
	free_mtx(coords);
	free_mtx(res);
}

void	hyperboloid_init(t_data *data, char *line, int i)
{
	char		**res;
	char		**coords;
	t_hyperboloid	*hyperboloid;

	data->obj[i].type_obj = HYPERBOLOID;
	hyperboloid = (t_hyperboloid *)safe_malloc(sizeof(t_hyperboloid)); 
	data->obj[i].object = hyperboloid;
	res = ft_split(line, ' ');

	coords = ft_split(res[1], ',');
	hyperboloid->pos.x = ft_atol(coords[0]);
	hyperboloid->pos.y = ft_atol(coords[1]);
	hyperboloid->pos.z = ft_atol(coords[2]);

	coords = ft_split(res[2], ',');
	hyperboloid->dir.x = ft_atol(coords[0]);
	hyperboloid->dir.y = ft_atol(coords[1]);
	hyperboloid->dir.z = ft_atol(coords[2]);
	hyperboloid->dir = normalize(hyperboloid->dir);
	free_mtx(coords);

	coords = ft_split(res[3], ',');
	hyperboloid->a = ft_atol(coords[0]);
	hyperboloid->b = ft_atol(coords[1]);
	hyperboloid->c = ft_atol(coords[2]);
	free_mtx(coords);

	coords = ft_split(res[4], ',');
	hyperboloid->rgb.r = ft_atol(coords[0]);
	hyperboloid->rgb.g = ft_atol(coords[1]);
	hyperboloid->rgb.b = ft_atol(coords[2]);
	free_mtx(coords);
	free_mtx(res);
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
	res = ft_split(line, ' ');
	data->ambient.ratio = ft_atol(res[1]);
	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[2], ',');
	data->ambient.rgb.r = ft_atol(rgb[0]);
	data->ambient.rgb.g = ft_atol(rgb[1]);
	data->ambient.rgb.b = ft_atol(rgb[2]);
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
	res = ft_split(line, ' ');

	coords = ft_split(res[1], ',');
	data->camera.pos.x = ft_atol(coords[0]);
	data->camera.pos.y = ft_atol(coords[1]);
	data->camera.pos.z = ft_atol(coords[2]);

	vector = ft_split(res[2], ',');
	data->camera.dir.x = ft_atol(vector[0]);
	data->camera.dir.y = ft_atol(vector[1]);
	data->camera.dir.z = ft_atol(vector[2]);

	data->camera.fov = ft_atoi(res[3]);
	data->camera.forward = normalize(data->camera.dir);
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
}

void lights_init(t_data *data, char *line, int nb_lights)
{
    if (nb_lights == 0) {
        data->lights = safe_malloc(sizeof(t_light) * 10);
    }
    char **res = ft_split(line, ' ');
    char **coords;
    char **rgb;

    coords = safe_malloc(sizeof(float) * 4);
	coords = ft_split(res[1], ',');
    data->lights[nb_lights].pos.x = ft_atol(coords[0]);
    data->lights[nb_lights].pos.y = ft_atol(coords[1]);
    data->lights[nb_lights].pos.z = ft_atol(coords[2]);

    data->lights[nb_lights].bright = ft_atol(res[2]);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
    data->lights[nb_lights].rgb.r = ft_atoi(rgb[0]);
    data->lights[nb_lights].rgb.g = ft_atoi(rgb[1]);
    data->lights[nb_lights].rgb.b = ft_atoi(rgb[2]);
}

void	pic_init(t_data *data, char *line, int nb_pics)
{
	char **res;
	char **part;
	t_picture	pic;

	res = ft_split(line, ' ');

	part = ft_split(res[1], ':');
	pic.path = part[1];
	pic.data = NULL;
	printf("path: %s\n", pic.path);
	pic.pic = mlx_xpm_file_to_image(data->mlx_ptr, pic.path, &pic.w, &pic.h);
	if (!pic.pic)
	{
		fprintf(stderr, "Error: Failed to load image from path %s\n", pic.path);
		free_mtx(res);
		free_mtx(res);
		return;
	}
	pic.data = mlx_get_data_addr(pic.pic, &pic.bpp, &pic.line_len, &pic.endian);
	pic.index = nb_pics;
	data->pic_idx = nb_pics;
	data->pics[nb_pics] = pic;
	/* free_mtx(part); */
	/* free_mtx(res); */
}
