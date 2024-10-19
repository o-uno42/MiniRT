/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/10/19 17:54:44 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

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
	data->ambient.rgb_1 = ft_atoi(rgb[0]);
	data->ambient.rgb_2 = ft_atoi(rgb[1]);
	data->ambient.rgb_3 = ft_atoi(rgb[2]);
    res = res;
	printf("AMBIENT\nRatio: %f\nrgb: %i\n%i\n%i\n\n", data->ambient.ratio, data->ambient.rgb_1, data->ambient.rgb_2, data->ambient.rgb_3);

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
	data->camera.x = ft_atoi(coords[0]);
	data->camera.y = ft_atoi(coords[1]);
	data->camera.z = ft_atoi(coords[2]);

	vector = safe_malloc(sizeof(float) * 4);
	vector = ft_split(res[3], ',');
	data->camera.vx = ft_atoi(vector[0]);
	// data->camera.vy = ft_atoi(vector[1]);
	// data->camera.vz = ft_atoi(vector[2]);

	data->camera.fov = ft_atoi(res[4]);
	printf ("CAMERA\nx: %f\ny: %f\nz: %f\nvx: %f\nvy: %f\nvz: %f\n\n", 
		data->camera.x, data->camera.y, data->camera.z, data->camera.vx, data->camera.vy, data->camera.vz);
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

	data->light.x = ft_atoi(coords[0]);
	data->light.y = ft_atoi(coords[1]);
	data->light.z = ft_atoi(coords[2]);

	data->light.bright = ft_atoi(res[2]);

	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[3], ',');
	data->light.rgb_1 = ft_atoi(rgb[0]);
	data->light.rgb_2 = ft_atoi(rgb[1]);
	data->light.rgb_3 = ft_atoi(rgb[2]);
	printf("LIGHT\nCoords: %f\n%f\n%f\nBright: %f\nRgb: %i\n%i\n%i\n\n", 
		data->light.x, data->light.y, data->light.z, data->light.bright,
			data->light.rgb_1, data->light.rgb_2, data->light.rgb_3);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}


static void	render_scene(int x, int y, t_data *data)
{
	my_pixel_put(data, x, y, MAGENTA);
}

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
			render_scene(x, y, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}
