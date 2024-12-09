/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:13 by thiew             #+#    #+#             */
/*   Updated: 2024/12/09 16:59:35 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	raycasting(int x, int y, t_data *data)
{
	x = x;
	y = y;
	data = data;
}

int	keys(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		write(1, "Hai chiuso il programma.\n", 25);
		mlx_loop_end(data->mlx_ptr);
	}
	return (0);
}

int	esc_x(t_data *data)
{
	write(1, "Hai chiuso il programma.\n", 25);
	mlx_loop_end(data->mlx_ptr);
	return (0);
}
