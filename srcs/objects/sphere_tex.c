/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:28:47 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/29 14:53:48 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_rgb	tex_sphere_color(t_hitinfo *hit, t_picture pic, t_sphere *sphere)
{
	float	theta;
	float	phi;
	float	scale_theta;
	float	square_theta;
	float	square_phi;
	int		tex_theta;
	int		tex_phi;
	t_rgb	final;

	theta = atan2(hit->normal.z, hit->normal.x);
	phi = acos(hit->normal.y / sphere->radius);
	scale_theta = sphere->radius / 1.5; 
	square_theta = fmod(theta / (ANGLE_SIZE * scale_theta), 1.0);
	square_phi = fmod(phi / (ANGLE_SIZE), 1.0);
	if (square_theta < 0)
		square_theta += 1.0;
	if (square_phi < 0)
		square_phi += 1.0;
	tex_theta = (int)(square_theta * pic.w);
	tex_phi = (int)(square_phi * pic.h);
	
    int color_offset = tex_phi * pic.line_len + tex_theta * (pic.bpp / 8);
    int color = *(int *)(pic.data + color_offset);
	final = extract_color_from_int(color);
	return (final);
}

void	sphere_texture(t_hitinfo *hit, t_sphere *sphere)
{

	if (sphere->nb_params < 5 || sphere->checker == false)
	{
		hit->rgb = sphere->rgb;
		return ;
	}
    hit->rgb = tex_sphere_color(hit, sphere->tex, sphere);
}

void	sphere_bump(t_hitinfo *hit, t_sphere *sphere)
{

	t_rgb	normal_color;
	t_vect	color_vect;
	t_vect	delta;

	if (sphere->nb_params != 6 || sphere->checker == false)
    {
        return;
    }
	normal_color = tex_sphere_color(hit, sphere->tex_normal, sphere);
	color_vect = rgb_to_vect(normal_color);
	delta = sub_vect(scale_down(color_vect, 127.5f), create_vector(1.0, 1.0, 1.0));
	hit->normal = normalize(delta);
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

