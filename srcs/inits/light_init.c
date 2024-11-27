/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:06:05 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/26 18:07:16 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	light_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**rgb;

	res = ft_split(line, ' ');
	coords = ft_split(res[1], ',');
	rgb = ft_split(res[3], ',');
	data->light.pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]), ft_atol(coords[2]));
	data->light.rgb = extract_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	data->light.bright = ft_atol(res[2]);
	free(coords);
	free(rgb);
	free(res);
}

void	lights_init(t_data *data, char *line, int nb_lights)
{
	char	**res;
	char	**coords;
	char	**rgb;

	res = ft_split(line, ' ');
	coords = ft_split(res[1], ',');
	rgb = ft_split(res[3], ',');
	data->lights[nb_lights].pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]), ft_atol(coords[2]));
	data->lights[nb_lights].rgb = extract_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	data->lights[nb_lights].bright = ft_atol(res[2]);
	data->light_idx = nb_lights;
	free(coords);
	free(rgb);
	free(res);
}
