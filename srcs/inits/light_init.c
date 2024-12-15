/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:06:05 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/15 16:14:20 by tjuvan           ###   ########.fr       */
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
	data->light.pos = create_vector(atol_wrapper(coords[0], data), atol_wrapper(coords[1], data),
			atol_wrapper(coords[2], data));
	data->light.rgb = extract_color(nb_atoi(data, rgb[0]), nb_atoi(data, rgb[1]),
			nb_atoi(data, rgb[2]));
	data->light.bright = atol_wrapper(res[2], data);
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
	data->lights[nb_lights].pos = create_vector(atol_wrapper(coords[0], data),
			atol_wrapper(coords[1], data), atol_wrapper(coords[2], data));
	data->lights[nb_lights].rgb = extract_color(nb_atoi(data, rgb[0]),
			nb_atoi(data, rgb[1]), nb_atoi(data, rgb[2]));
	data->lights[nb_lights].bright = atol_wrapper(res[2], data);
	free_all_mtx(res, coords, rgb, NULL);
}
