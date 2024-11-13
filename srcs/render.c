/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/11/13 17:51:42 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dest;

	offset = (y * data->img.line_len + x * (data->img.bpp / 8));
	dest = data->img.pix_ptr + offset;
	*(unsigned int *)dest = color;
}


void	render_objs(t_data *data, t_ray camera_ray, t_hitinfo *hit)
{
	int i;
	t_type_obj	type;
	
	i = 0;
	while (data->obj[i].type_obj != END)
	{
		type = data->obj[i].type_obj;
		if (type == SPHERE)
		{
			render_sphere(camera_ray, data, data->obj[i].object, hit);
		}
		else if (type == PLANE)
		{
			render_plane(camera_ray, data->obj[i].object, hit);
		}
		else if(type == CYLINDER)
		{
			render_cylinder(camera_ray, data, data->obj[i].object, hit);
		}
		else if(type == HYPERBOLOID)
			render_hyperboloid(camera_ray,data, data->obj[i].object, hit);	
		else if (type == CONE)
			render_cone(camera_ray, data, data->obj[i].object, hit);
		i++;
	}
}

int    render(t_data *data)
{
	int	x;
	int	y;
	t_ray camera_ray;
	t_hitinfo hit;
	/* t_ray *rays = light_rays(data); */
	// int i;

	/* print_all_obj(data); */
	data->img_ratio = ratio(data->img.width, data->img.height);
	print_camera(data->camera);
	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			hit = init_hit(data);
			data->hit = hit;
			/* printf(" cords: x: %d, y: %d,\thit is: %f\n",x ,y, data->hit.t); */
			camera_ray = camera_rays(x, y,data);
			render_objs(data, camera_ray, &data->hit);
			/* light_intersect(data, rays, &data->hit); */
				// my_pixel_put(data, x, y, WHITE);
			my_pixel_put(data, x, y, create_color(data->hit.rgb, data->ambient));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}
