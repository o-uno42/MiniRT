/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:13 by thiew             #+#    #+#             */
/*   Updated: 2024/11/28 18:24:24 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	raycasting(int x, int y, t_data *data)
{
	x = x;
	y = y;
	data = data;
}

// void	render(t_map *map)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y <= map->height)
// 	{
// 		x = 0;
// 		while (x <= map->width)
// 		{
// 			//raycasting(x, y, map);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(map->mlx_ptr, map->mlx_window, 
// 		map->img.img_ptr, 0, 0);
// }	

int	keys(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		write (1, "Hai chiuso il programma.\n", 25);
		mlx_loop_end(data->mlx_ptr);
		/* mlx_destroy_window(data->mlx_ptr, data->mlx_win); */
		/* clean(data); */
		/* mlx_destroy_image(data->img.img_ptr, data->img.pix_ptr); */
		/* mlx_destroy_display(data->mlx_ptr); */
		/* free(data->mlx_ptr); */
		/* free(data->mlx_ptr); */
	}
	return (0);
}

int	esc_x(t_data *data)
{
	write (1, "Hai chiuso il programma.\n", 25);
	mlx_loop_end(data->mlx_ptr);
	/* clean(data); */
	/* mlx_destroy_window(data->mlx_ptr, data->mlx_win); */
	/* mlx_destroy_image(data->img.img_ptr, data->img.pix_ptr); */
	/* mlx_destroy_display(data->mlx_ptr); */
	/* free(data->mlx_ptr); */
	/* free(data->mlx_ptr); */
	return(0);
}
