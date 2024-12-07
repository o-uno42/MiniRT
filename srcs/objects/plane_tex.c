/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:31:09 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/03 18:19:12 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdbool.h>

t_rgb	tex_color(t_hitinfo *hit, t_picture pic)
{
	int		color_offset;
	int		color;
	t_rgb	color_v;
	t_calc	calc;

	calc = hit->calc;
	calc.u = fmod(hit->p.x / SQUARE, 1.0);
	calc.v = fmod(hit->p.z / SQUARE, 1.0);
	if (calc.u < 0)
		calc.u += 1.0;
	if (calc.v < 0)
		calc.v += 1.0;
	calc.tex_x = (int)(calc.u * pic.w);
	calc.tex_y = (int)(calc.v * pic.h);
	color_offset = calc.tex_y * pic.line_len + calc.tex_x * (pic.bpp / 8);
	color = *(int *)(pic.data + color_offset);
	color_v = extract_color_from_int(color);
	return (color_v);
}


t_rgb	tex_color_plane(t_plane *plane, t_hitinfo *hit, t_picture pic)
{
    float u;
    float v;

	float dot1;
	float dot2;
	float dot3;

	int tex_x;
	int tex_y;

	bool orientation;

	orientation = false;

	dot1 = fabs(dot_product(plane->vect, create_vector(1, 0, 0)));
	dot2 = fabs(dot_product(plane->vect, create_vector(0, 1, 0)));
	dot3 = fabs(dot_product(plane->vect, create_vector(0, 0, 1)));

	if (!((dot1 > dot3) && !(dot1 > dot2)) && (dot2 > dot3))
	{
		u = fmod(hit->p.x / SQUARE, 1.0);
		v = fmod(hit->p.z / SQUARE, 1.0);
		orientation = true;
	}
	else if ((dot1 > dot3) && !(dot1 > dot2)) 
	{
		u = fmod(hit->p.z / SQUARE, 1.0);
		v = fmod(hit->p.x / SQUARE, 1.0);
		orientation = true;
	}
	else if (!((dot1 > dot3) && !(dot1 > dot2)) && (dot2 < dot3)) 
	{
		u = fmod(hit->p.y / SQUARE, 1.0);
		v = fmod(hit->p.x / SQUARE, 1.0);
		orientation = false;
	}
	else
	{
		u = fmod(hit->p.y / SQUARE, 1.0);
		v = fmod(hit->p.z / SQUARE, 1.0);
		orientation = false;
	}
    if (u < 0) u += 1.0;
    if (v < 0) v += 1.0;

	if (orientation)
	{
		tex_x = (int)(u * pic.w);
		tex_y = (int)(v * pic.h);
	}
	else
	{
		tex_y = (int)(u * pic.w);
		tex_x = (int)(v * pic.h);
	}
    int color_offset = tex_y * pic.line_len + tex_x * (pic.bpp / 8);
    int color = *(int *)(pic.data + color_offset);
	t_rgb color_v = extract_color_from_int(color);
	return (color_v);
}

void plane_texture(t_hitinfo *hit, t_plane *plane, t_picture pic)
{
    if (plane->nb_params < 5 || plane->checker == false)
        return;
    hit->rgb = tex_color_plane(plane, hit, pic);
}

void	plane_checker(t_hitinfo *hit, t_plane *plane)
{
	int	square_x;
	int	square_y;
	int	square_z;

	if (plane->checker == false && plane->nb_params > 4)
	{
		hit->rgb = plane->rgb;
		return ;
	}
	square_x = floor(hit->p.x / SQUARE);
	square_y = floor(hit->p.y / SQUARE);
	square_z = floor(hit->p.z / SQUARE);
	if ((square_x + square_y + square_z) % 2 == 0)
		hit->rgb = plane->rgb;
	else
		hit->rgb = extract_color(0, 0, 0);
}

void	plane_bump(t_hitinfo *hit, t_plane *plane)
{
	t_rgb	normal_color;
	t_vect	color_vect;
	t_vect	delta;

	if (plane->nb_params != 6 || plane->checker == false)
	{
		return ;
	}
	normal_color = tex_color_plane(plane, hit, plane->tex_norm);
	color_vect = rgb_to_vect(normal_color);
	delta = sub_vect(scale_down(color_vect, 127.5f), create_vector(1.0, 1.0,
				1.0));
	hit->normal = normalize(delta);
}


// t_rgb	tex_color(t_hitinfo *hit, t_picture pic)
// {
//     float u = fmod(hit->p.x / SQUARE, 1.0);
//     float v = fmod(hit->p.z / SQUARE, 1.0);

//     if (u < 0) u += 1.0;
//     if (v < 0) v += 1.0;

//     int tex_x = (int)(u * pic.w);
//     int tex_y = (int)(v * pic.h);

//     int color_offset = tex_y * pic.line_len + tex_x * (pic.bpp / 8);
//     int color = *(int *)(pic.data + color_offset);
// 	t_rgb color_v = extract_color_from_int(color);
// 	return (color_v);
// }

t_vect	positive_vect(t_vect vect)
{
	if (vect.x < 0)
		vect.x = -vect.x;
	if (vect.y < 0)
		vect.y = -vect.y;
	if (vect.z < 0)
		vect.z = -vect.z;
	return vect;
}
