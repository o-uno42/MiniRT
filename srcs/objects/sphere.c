/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:48 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/13 17:17:11 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	sphere_texture(t_hitinfo *hit, t_sphere *sphere)
{
	float	theta;
	float	phi;
	float	scale_theta;
	float	square_theta;
	float	square_phi;
	int		tex_theta;
	int		tex_phi;

	if (sphere->checker == false || sphere->tex.data == NULL)
	{
		hit->rgb = sphere->rgb;
		return ;
	}
	theta = atan2(hit->normal.z, hit->normal.x);
	phi = acos(hit->normal.y / sphere->radius);
	scale_theta = sphere->radius / 1.5; 
	square_theta = fmod(theta / (ANGLE_SIZE * scale_theta), 1.0);
	square_phi = fmod(phi / (ANGLE_SIZE), 1.0);
	if (square_theta < 0)
		square_theta += 1.0;
	if (square_phi < 0)
		square_phi += 1.0;
	tex_theta = (int)(square_theta * sphere->tex.w);
	tex_phi = (int)(square_phi * sphere->tex.h);
	
    int color_offset = tex_phi * sphere->tex.line_len + tex_theta * (sphere->tex.bpp / 8);
    int color = *(int *)(sphere->tex.data + color_offset);

    hit->rgb = extract_color_from_int(color);


}

void	checker_sphere(t_hitinfo *hit, t_sphere *sphere)
{
	float	theta;
	float	phi;
	float	scale_theta;
	int		square_theta;
	int		square_phi;

	if (sphere->checker == false)
	{
		hit->rgb = sphere->rgb;
		return ;
	}
	theta = atan2(hit->normal.z, hit->normal.x);
	phi = acos(hit->normal.y / sphere->radius);
	scale_theta = sphere->radius / 1.5; 
	square_theta = floor(theta / (ANGLE_SIZE * scale_theta));
	square_phi = floor(phi / (ANGLE_SIZE));
	if ((square_theta + square_phi) % 2 == 0)
		hit->rgb = sphere->rgb;
	else
		hit->rgb = extract_color( 0, 0 , 0);
}

void	calc_hit_sphere(t_hitinfo *hit, float intersect, t_ray ray, t_sphere *sphere)
{
	if (intersect >= hit->t)
		return ;
	hit->t = intersect;
	hit->p = sum_vect(ray.pos, scale_vect(ray.dir, intersect));
	hit->normal = normalize(sub_vect(hit->p, sphere->pos));
	if (dot_product(ray.dir, hit->normal) < 0)
		hit->is_outside = true;
	else
	{
		hit->normal = scale_vect(hit->normal, -1);
		hit->is_outside = false;
	}
	/* checker_sphere(hit, sphere); */
	sphere_texture(hit, sphere);
}

bool	render_sphere(t_ray camera_ray, t_data *data, t_sphere *sphere, t_hitinfo *hit)
{
	data = data;
	t_vect	offset_vect;
	float	intersect1;
	float	intersect2;

	offset_vect = sub_vect(camera_ray.pos, sphere->pos);

	float a = dot_product(camera_ray.dir, camera_ray.dir);
	float b = 2.0 * dot_product(camera_ray.dir, offset_vect);
	float c = dot_product(offset_vect, offset_vect) - square((*sphere).radius);
	if (solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0)
		{
			calc_hit_sphere(hit, intersect1, camera_ray, sphere);
			return (true);
		}
	}
	intersect1 = FLT_MAX;
	calc_hit_sphere(hit, intersect1, camera_ray, sphere);
	return (false);
}

