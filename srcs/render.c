/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/10/19 17:54:44 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    ambient_init(t_data *data, char *line)
{
    int     i;
    char    **res;

    i = 0;
    i= i;
    data = data;
    res = NULL;
    line = line;
    // res = safe_malloc(sizeof(char *) * 2); 
    // res = ft_split_rt(line, ',');
    res = res;

}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}


static void	render_scene(int x, int y, t_data *data)
{
	my_pixel_put(data, x, y, MAGENTA);
}

int    render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->img.height)
	{
		x = 0;
		while (x <= data->img.width)
		{
			render_scene(x, y, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}
