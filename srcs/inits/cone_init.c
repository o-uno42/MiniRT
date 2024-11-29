/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:32:31 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/29 13:26:53 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	top_bottom_cone(POINT *p1, POINT *p2, t_cone cone)
{
	*p1 = sum_vect(cone.pos, scale_vect(cone.dir, cone.height / 2));
	*p2 = sum_vect(cone.pos, scale_vect(cone.dir, -cone.height / 2));
}

void	cone_angle(t_cone *cone)
{
	float	angle;

	angle = atan2((*cone).radius, (*cone).height / 2);
	(*cone).theta_r = angle;
	(*cone).theta_d = angle * (180 / M_PI);
}

void	cone_vect_init(t_cone *cone, char **res, char **coords)
{
	POINT	p1;
	POINT	p2;

	cone->pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	free_mtx(coords);
	coords = ft_split(res[2], ',');
	cone->dir = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
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
	cone->rgb = extract_color(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	free_mtx(coords);
}

void	cone_bonus_init(t_cone *cone, char **res, int count)
{
	cone->tex.data = NULL;
	if (count >= 6 &&res[6] && (ft_atoi(res[6]) == 0 || ft_atoi(res[6]) == 1))
	{
		cone->checker = ft_atoi(res[6]);
		cone->bonus = ft_atoi(res[6]);
	}
	else
	{
		cone->checker = false;
		cone->bonus = false;
	}
	cone->nb_params = count;
	// if (res[7])
	// 	cone->brilliance = ft_atol(res[7]);
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
	count = mtx_count(res);
	coords = ft_split(res[1], ',');
	cone_vect_init(cone, res, coords);
	cone_bonus_init(cone, res, count);
	free_mtx(res);
}
