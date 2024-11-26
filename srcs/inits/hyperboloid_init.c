/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:07:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/26 13:13:23 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	hyperboloid_vect_init(t_hyperboloid *hyperboloid, char **res,
		char **coords)
{
	hyperboloid->pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	free_mtx(coords);
	coords = ft_split(res[2], ',');
	hyperboloid->dir = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	hyperboloid->dir = normalize(hyperboloid->dir);
	free_mtx(coords);
	coords = ft_split(res[3], ',');
	hyperboloid->a = ft_atol(coords[0]);
	hyperboloid->b = ft_atol(coords[1]);
	hyperboloid->c = ft_atol(coords[2]);
	free_mtx(coords);
	coords = ft_split(res[4], ',');
	hyperboloid->rgb = extract_color(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	free_mtx(coords);
}

void	hyperboloid_init(t_data *data, char *line, int i)
{
	char			**res;
	char			**coords;
	t_hyperboloid	*hyperboloid;

	data->obj[i].type_obj = HYPERBOLOID;
	hyperboloid = (t_hyperboloid *)safe_malloc(sizeof(t_hyperboloid));
	data->obj[i].object = hyperboloid;
	res = ft_split(line, ' ');
	coords = ft_split(res[1], ',');
	hyperboloid_vect_init(hyperboloid, res, coords);
	free_mtx(res);
}
