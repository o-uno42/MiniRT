/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:22 by thiew             #+#    #+#             */
/*   Updated: 2024/11/14 16:38:24 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <time.h>
// #include <climits>

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
	// hit->rgb = create_color_rgb(hit->rgb, data->ambient);
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
	int z;
	t_ray camera_ray;
	t_hitinfo hit;
	t_ray **bonus_rays = NULL;

	z = 0;
	printf("--------------Main nb_lights: %i\n", data->nb_lights);
	printf ("POS LIGHT BONUS :\n");
	print_vect(data->light_bonus[0].pos);
	data->img_ratio = ratio(data->img.width, data->img.height);
	print_camera(data->camera);
	y = 0;
	z = 0;
	z = z;
	int d = 0;
	// float res = 0;

	// t_ray		*rays = light_rays(data);

	bonus_rays = safe_malloc(data->nb_lights * sizeof(t_ray *));
	while (d < data->nb_lights)
	{
		bonus_rays[d] = light_bonus_rays(data, d);
		d++;
	}
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			hit = init_hit(data);
			data->hit = hit;
			camera_ray = camera_rays(x, y,data);
			render_objs(data, camera_ray, &data->hit);
			// t_rgb res = light_intersect(data, rays, camera_ray, &data->hit, x, y);
			t_rgb res = super_light_bonus_intersect(data, bonus_rays, camera_ray, &data->hit, x, y);
			// hit.rgb = light_bonus_intersect(data, bonus_rays, camera_ray, &data->hit, d, x, y);
			my_pixel_put(data, x, y, just_color(res));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}
