/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:32:06 by tjuvan            #+#    #+#             */
/*   Updated: 2024/10/20 18:33:09 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	data->plane.pos.x = ft_atol(coords[0]);
	data->plane.pos.y = ft_atol(coords[1]);
	data->plane.pos.z = ft_atol(coords[2]);

	// printf("%f", data->plane.pos.z);

	data->plane.posn.x = data->plane.pos.x;
	data->plane.posn.y = data->plane.pos.y + 10;
	data->plane.posn.z = data->plane.pos.z;

	vect = safe_malloc(sizeof(char *) * 4);
	vect = ft_split(res[2],  ',');
	data->plane.vect.x = ft_atol(vect[0]);
	data->plane.vect.y = ft_atol(vect[1]);
	data->plane.vect.z = ft_atol(vect[2]);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->plane.rgb.r = ft_atol(rgb[0]);
	data->plane.rgb.g = ft_atol(rgb[1]);
	data->plane.rgb.b = ft_atol(rgb[2]);
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
	data->sphere.pos.x = ft_atol(coords[0]);
	data->sphere.pos.y = ft_atol(coords[1]);
	data->sphere.pos.z = ft_atol(coords[2]);

	data->sphere.diameter = ft_atol(res[2]);
	data->sphere.radius = (data->sphere.diameter/2);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->sphere.rgb.r = ft_atol(rgb[0]);
	data->sphere.rgb.g = ft_atol(rgb[1]);
	data->sphere.rgb.b = ft_atol(rgb[2]);
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

	res = safe_malloc(sizeof(float) * 4);
	res = ft_split(line, ' ');

	coords = safe_malloc(sizeof(float) * 4);
	coords = ft_split(res[2], ',');
	data->camera.pos.x = ft_atol(coords[0]);
	data->camera.pos.y = ft_atol(coords[1]);
	data->camera.pos.z = ft_atol(coords[2]);

	vector = safe_malloc(sizeof(float) * 4);
	vector = ft_split(res[3], ',');
	data->camera.dir.x = ft_atol(vector[0]);
	// data->camera.dir.y = ft_atol(vector[1]);
	// data->camera.dir.z = ft_atol(vector[2]);
	// data->camera.vy = ft_atol(vector[1]);
	// data->camera.vz = ft_atol(vector[2]);

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
