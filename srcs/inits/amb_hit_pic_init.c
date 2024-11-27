/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_hit_pic_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:57:53 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/26 18:08:38 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_hitinfo	init_hit(t_data *data)
{
	t_hitinfo	hit;

	hit.p = create_vector(0, 0, 0);
	hit.t = FLT_MAX;
	hit.normal = create_vector(0, 0, 0);
	hit.rgb = data->ambient.rgb;
	return (hit);
}

void	ambient_init(t_data *data, char *line)
{
	int		i;
	int		j;
	char	**res;
	char	**rgb;

	i = 0;
	i = i;
	j = 0;
	j = j;
	res = ft_split(line, ' ');
	data->ambient.ratio = ft_atol(res[1]);
	rgb = safe_malloc(sizeof(int) * 4);
	rgb = ft_split(res[2], ',');
	data->ambient.rgb = extract_color(ft_atol(rgb[0]), ft_atol(rgb[1]),
			ft_atol(rgb[2]));
}

void	pic_init(t_data *data, char *line, int nb_pics)
{
	char		**res;
	char		**part;
	t_picture	pic;

	res = ft_split(line, ' ');
	part = ft_split(res[1], ':');
	pic.path = ft_strdup(part[1]);
	pic.data = NULL;
	pic.pic = mlx_xpm_file_to_image(data->mlx_ptr, pic.path, &pic.w, &pic.h);
	if (!pic.pic)
	{
		fprintf(stderr, "Error: Failed to load image from path %s\n", pic.path);
		free_mtx(res);
		free_mtx(res);
		return ;
	}
	pic.data = mlx_get_data_addr(pic.pic, &pic.bpp, &pic.line_len, &pic.endian);
	pic.index = nb_pics;
	data->pic_idx = nb_pics;
	data->pics[nb_pics] = pic;
	free_mtx(part);
	free_mtx(res);
}
