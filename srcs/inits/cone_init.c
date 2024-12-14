/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:32:31 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/10 16:36:45 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	cone_vect_2(t_cone *cone, char **res, char **coords)
{
	POINT	p1;
	POINT	p2;

	cone->diameter = ft_atol(res[3]);
	cone->radius = cone->diameter / 2.0;
	cone->height = ft_atol(res[4]);
	cone_angle(cone);
	top_bottom_cone(&p1, &p2, *cone);
	cone->p1 = p1;
	cone->p2 = p2;
	coords = ft_split(res[5], ',');
	if (mtx_count(coords) != 2)
	{
		free(coords);
		return (false);
	}
	cone->rgb = extract_color(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	free_mtx(coords);
	return (true);
}

bool	cone_vect_init(t_cone *cone, char **res, char **coords)
{
	cone->pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	free_mtx(coords);
	coords = ft_split(res[2], ',');
	if (mtx_count(coords) != 2)
	{
		free(coords);
		return (false);
	}
	cone->dir = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	cone->dir = normalize(cone->dir);
	free_mtx(coords);
	if (!cone_vect_2(cone, res, coords))
		return (false);
	return (true);
}

void	cone_bonus_init(t_data *data, t_cone *cone, char **res, int count)
{
	cone->tex.data = NULL;
	if (count >= 6 && res[6] && (nb_atoi(data, res[6]) == 0 || nb_atoi(data, res[6]) == 1))
	{
		cone->checker = nb_atoi(data, res[6]);
		cone->bonus = nb_atoi(data, res[6]);
	}
	else
	{
		cone->checker = false;
		cone->bonus = false;
	}
	cone->nb_params = count;
}

void	cone_init(t_data *data, char *line, int i)
{
	char	**res;
	char	**coords;
	t_cone	*cone;
	int		count;

	data->obj[i].type_obj = CONE;
	cone = (t_cone *)safe_malloc(sizeof(t_cone));
	data->obj[i].object = cone;
	res = ft_split(line, ' ');
	if (invalid_params(res, 5, data))
		return ;
	count = mtx_count(res);
	if (invalid_parts(&coords, 2, data, res[1]))
	{
		free_all_mtx(res, coords, NULL, NULL);
		return ;
	}
	cone_vect_init(cone, res, coords);
	cone_bonus_init(data, cone, res, count);
	free_mtx(res);
}
