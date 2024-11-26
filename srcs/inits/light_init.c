/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:06:05 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/26 13:06:54 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	light_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**rgb;

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

void	lights_init(t_data *data, char *line, int nb_lights)
{
	char	**res;
	char	**coords;
	char	**rgb;

	if (nb_lights == 0)
	{
		data->lights = safe_malloc(sizeof(t_light) * 10);
	}
	res = ft_split(line, ' ');
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
