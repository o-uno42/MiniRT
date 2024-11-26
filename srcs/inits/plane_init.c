/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:13:20 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/26 12:30:01 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	plane_vect_init(char **coords, char **vect, char **rgb, t_plane *plane)
{
	plane->pos = create_vector(ft_atol(coords[0]), ft_atol(coords[1]),
			ft_atol(coords[2]));
	plane->posn.x = plane->pos.x;
	plane->posn.y = plane->pos.y + 10;
	plane->posn.z = plane->pos.z;
	plane->vect = create_vector(ft_atol(vect[0]), ft_atol(vect[1]),
			ft_atol(vect[2]));
	plane->vect = normalize(plane->vect);
	plane->rgb = extract_color(ft_atol(rgb[0]), ft_atol(rgb[1]),
			ft_atol(rgb[2]));
}

void	plane_bonus_init(char **res, t_plane *plane, t_data *data)
{
	if (res[4] && (ft_atoi(res[4]) == 0 || ft_atoi(res[4]) == 1))
	{
		plane->checker = ft_atoi(res[4]);
		plane->bonus = ft_atoi(res[4]);
	}
	else
	{
		plane->checker = false;
		plane->bonus = false;
	}
	if (res[5])
		plane->tex = data->pics[ft_atoi(res[5])];
	if (res[6])
		plane->tex_norm = data->pics[ft_atoi(res[6])];
}

void	plane_init(t_data *data, char *line, int i)
{
	char	**res;
	char	**coords;
	char	**vect;
	char	**rgb;
	t_plane	*plane;

	data->obj[i].type_obj = PLANE;
	plane = (t_plane *)safe_malloc(sizeof(t_plane));
	data->obj[i].object = plane;
	res = ft_split(line, ' ');
	coords = ft_split(res[1], ',');
	vect = ft_split(res[2], ',');
	rgb = ft_split(res[3], ',');
	plane_vect_init(coords, vect, rgb, plane);
	plane_bonus_init(res, plane, data);
	free_mtx(rgb);
	free_mtx(vect);
	free_mtx(coords);
	free_mtx(res);
}
