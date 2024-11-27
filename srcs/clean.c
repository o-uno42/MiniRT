/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:06 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/26 18:26:15 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clean_geometry(t_objs *obj)
{
	int	i;

	i = 0;
	while (obj->type_obj != END)
	{
		free(obj[i++].object);
		free(obj);
	}
}

void	clean_pics(t_picture pics[], int pic_idx)
{
	int	i;

	i = 0;
	while(i <= pic_idx && pics[i].data != NULL)
	{
		free(pics[i].path);
		free(pics[i].data);
		free(pics[i].pic);
	}
}

void clean(t_data *data, int fd)
{

	clean_geometry(data->obj);
	clean_pics(data->pics, data->pic_idx);
	close(fd);
}
