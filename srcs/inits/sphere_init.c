/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:42:03 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/28 14:15:30 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	sphere_bonus_init(t_data *data, t_sphere *sphere, char **res)
{
	int	count;

	count = mtx_count(res);
	if (count >= 4 && res[4] && (ft_atoi(res[4]) == 0 || ft_atoi(res[4]) == 1))
	{
		sphere->checker = ft_atoi(res[4]);
		sphere->bonus = ft_atoi(res[4]);
	}
	else
	{
		sphere->checker = false;
		sphere->bonus = false;
	}
	if (count >= 5 && res[5])
		sphere->tex = data->pics[ft_atoi(res[5])];
	if (count >= 6 && res[6])
		sphere->tex_normal = data->pics[ft_atoi(res[6])];
	// if (res[7])
	// 	sphere->brilliance = ft_atol(res[7]);
}

void	sphere_init(t_data *data, char *line, int i)
{
	char		**res;
	char		**coords;
	char		**rgb;
	t_sphere	*sphere;

	data->obj[i].type_obj = SPHERE;
	sphere = (t_sphere *)safe_malloc(sizeof(t_sphere));
	data->obj[i].object = sphere;
	res = ft_split(line, ' ');
	coords = ft_split(res[1], ',');
	rgb = ft_split(res[3], ',');
	sphere->pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	sphere->diameter = ft_atol(res[2]);
	sphere->radius = sphere->diameter / 2;
	sphere->rgb = extract_color(ft_atol(rgb[0]), ft_atol(rgb[1]),
			ft_atol(rgb[2]));
	sphere_bonus_init(data, sphere, res);
	free_mtx(rgb);
	free_mtx(coords);
	free_mtx(res);
}
