/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:01:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/28 17:08:33 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	world_position(t_data *data, t_vect world_up)
{
	if (data->camera.dir.x == 0 && data->camera.dir.z == 0)
	{
		data->camera.right = create_vector(1.0, 0, 0);
		data->camera.up = create_vector(0, 0, 1.0);
	}
	else
	{
		data->camera.right = normalize(cross_product(world_up,
					data->camera.forward));
		data->camera.up = cross_product(data->camera.forward,
				data->camera.right);
	}
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
	vector = ft_split(res[2], ',');
	data->camera.pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	data->camera.dir = create_vector(ft_atol(vector[0]), ft_atol(vector[1]),
			ft_atol(vector[2]));
	data->camera.fov = ft_atoi(res[3]);
	data->camera.forward = normalize(data->camera.dir);
	world_position(data, world_up);
	free_mtx(coords);
	free_mtx(vector);
	free_mtx(res);
}
