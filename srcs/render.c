/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/10/19 20:59:10 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    ambient_init(t_data *data, char *line)
{
    int     i;
	int		j;
    char    **res;
	char	**rgb;

    i = 0;
    i= i;
	j =0;
	j = j;
	rgb = NULL;
	rgb = rgb;
    data = data;
    res = NULL;
    line = line;
    res = safe_malloc(sizeof(char *) * 3); 
    // res = ft_split_rt(line, ',');
	res = ft_split(line, ' ');
	// printf ("res 1 %s\n", res[0]);
	// printf ("res 1 %s\n", res[1]);
	// while (res[j])
	// 	j++;
	// if (j != 1)
	// 	print_error("Wrong parameters for Ambient Light");
	data->ambient->ratio = ft_atoi(res[1]);
	// rgb = safe_malloc(sizeof(int) * 4);
	// rgb = ft_split(line, ',');
	// data->ambient->rgb_1 = ft_atoi(rgb[0]);
	// data->ambient->rgb_2 = ft_atoi(rgb[1]);
	// data->ambient->rgb_3 = ft_atoi(rgb[2]);
    res = res;
	printf("%f, rgb: %i %i %i", data->ambient->ratio, data->ambient->rgb_1, data->ambient->rgb_2, data->ambient->rgb_3);

}

int	interpolate_color(int color1, int color2, float ratio)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = (int)(get_t(color1) * (1 - ratio) + get_t(color2) * ratio);
	r = (int)(get_r(color1) * (1 - ratio) + get_r(color2) * ratio);
	g = (int)(get_g(color1) * (1 - ratio) + get_g(color2) * ratio);
	b = (int)(get_b(color1) * (1 - ratio) + get_b(color2) * ratio);
	return (create_trgb(t, r, g, b));
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}

int	square(int i)
{
	return (i * i);
}

static void	render_scene(int x, int y, t_data *data)
{
	float	ratio;
	int		color;
	int		color2;
	int		d;

	d = sqrt(square(x - (data->img.width / 2)) + square(y - (data->img.height / 2)));
	ratio = (float)x / (float)data->img.width;
	color = interpolate_color(BLACK, MAGENTA, ratio);
	color2 = interpolate_color(YELLOW, BLACK, ratio);
	if (d > data->img.width / 4)
		my_pixel_put(data, x, y, color);
	else
		my_pixel_put(data, x, y, color2);

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

// a = PI *r^2
