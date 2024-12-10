/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:06:05 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/10 16:37:07 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	light_init(t_data *data, char *line)
{
	char	**res;
	char	**coords;
	char	**rgb;

	res = ft_split(line, ' ');
	if (invalid_params(res, 3, data))
		return ;
	if (invalid_parts(&coords, 2, data, res[1]) || invalid_parts(&rgb, 2, data,
			res[3]))
	{
		free_all_mtx(res, coords, rgb, NULL);
		return ;
	}
	data->light.pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	data->light.rgb = extract_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]),
			ft_atoi(rgb[2]));
	data->light.bright = ft_atol(res[2]);
	free_all_mtx(res, coords, rgb, NULL);
}

void	lights_init(t_data *data, char *line, int nb_lights)
{
	char	**res;
	char	**coords;
	char	**rgb;

	res = ft_split(line, ' ');
	if (invalid_params(res, 3, data))
		return ;
	if (invalid_parts(&coords, 2, data, res[1]) || invalid_parts(&rgb, 2, data,
			res[3]))
	{
		free_all_mtx(res, coords, rgb, NULL);
		return ;
	}
	data->lights[nb_lights].pos = create_vector(ft_atol(coords[0]),
			ft_atol(coords[1]), ft_atol(coords[2]));
	data->lights[nb_lights].rgb = extract_color(ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	data->lights[nb_lights].bright = ft_atol(res[2]);
	free_all_mtx(res, coords, rgb, NULL);
}
