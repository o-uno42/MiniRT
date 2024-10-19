/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:07 by thiew             #+#    #+#             */
/*   Updated: 2024/10/19 17:59:01 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
// #include <cstdlib>

static void	print_error(void)
{
	perror("Error");
}

void	img_init(t_img *img)
{
	img->img_ptr = mlx_init();
	if (!img->img_ptr)
		print_error();
}

void	*data_init(t_data *data)
{
	data->img.width = 900;
	data->img.height = 700;
	data->ambient = NULL;
	data->camera = NULL;
	data->light = NULL;
	return (data);
}
void	inits(t_data *data, t_img *img)
{
	img_init(img);
	data_init(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		print_error();
	data->mlx_win = mlx_new_window(data->mlx_ptr, \
		data->img.width, data->img.height, "miniRT");
	if (!data->mlx_win)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		print_error();
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, \
		data->img.width, data->img.height);
	if (!data->img.img_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		print_error();
	}
	data->img.pix_ptr = mlx_get_data_addr(data->img.img_ptr, \
		&data->img.bpp, &data->img.line_len, &data->img.endian);
}

int main(int ac, char **av)
{
	int		fd;
	t_data	data;
	t_img	img;
	ac = ac;

	fd = open(av[1], O_RDONLY);
	if (!fd)
		exit (EXIT_FAILURE);
	inits(&data, &img);
	parsing(fd, &data);
	mlx_hook(data.mlx_win, 2, 1L << 0, keys, &data);
	mlx_hook(data.mlx_win, 17, 1L << 2, esc_x, &data);
	render(&data);
	// mlx_mouse_hook(data.mlx_win, mouse_handler, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
