/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:13:20 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/07 16:36:17 by tjuvan           ###   ########.fr       */
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
	int	count;

	count = mtx_count(res);
	plane->tex.data = NULL;
	plane->tex_norm.data = NULL;
	if (count >= 4 && res[4] && (ft_atoi(res[4]) == 0 || ft_atoi(res[4]) == 1))
	{
		plane->checker = ft_atoi(res[4]);
		plane->bonus = ft_atoi(res[4]);
	}
	else
	{
		plane->checker = false;
		plane->bonus = false;
	}
	if (count >= 5 && res[5])
		plane->tex = data->pics[ft_atoi(res[5])];
	if (count >= 6 && res[6])
		plane->tex_norm = data->pics[ft_atoi(res[6])];
	// if (res[7])
	// 	plane->brilliance = ft_atol(res[7]);
	plane->nb_params = count;
	printf("plane->nb params: %d \n",plane->nb_params);
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
	if (invalid_params(res, 3, data))
			return ;
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
