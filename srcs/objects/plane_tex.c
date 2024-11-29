/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:31:09 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/15 16:31:32 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdbool.h>

t_rgb	tex_color(t_hitinfo *hit, t_picture pic)
{
    float u = fmod(hit->p.x / SQUARE, 1.0);
    float v = fmod(hit->p.z / SQUARE, 1.0);

    if (u < 0) u += 1.0;
    if (v < 0) v += 1.0;

    int tex_x = (int)(u * pic.w);
    int tex_y = (int)(v * pic.h);

    int color_offset = tex_y * pic.line_len + tex_x * (pic.bpp / 8);
    int color = *(int *)(pic.data + color_offset);
	t_rgb color_v = extract_color_from_int(color);
	return (color_v);
}

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

t_rgb	tex_color_plane(t_plane *plane, t_hitinfo *hit, t_picture pic)
{
    float u;
    float v;

	// t_rgb error = {150,150,150};

	float dot1;
	float dot2;
	float dot3;

	// t_vect positive_plane = positive_vect(plane->vect);

	int tex_x;
	int tex_y;

	bool orientation;

	orientation = false;

	dot1 =dot_product(plane->vect, create_vector(1, 0, 0));
	dot2 =dot_product(plane->vect, create_vector(0, 1, 0));
	dot3 =dot_product(plane->vect, create_vector(0, 0, 1));

	if (!((dot1 > dot3) && !(dot1 > dot2)) && (dot2 > dot3))
	{
		// res1 = dot_product(plane->vect, create_vector(1, 0, 0));
		// res2 = dot_product(plane->vect, create_vector(0, 0, 1));
		// printf("1 ] ");
		// printf("2 ] %f\n", res2);
		u = fmod(hit->p.x / SQUARE, 1.0);
		v = fmod(hit->p.z / SQUARE, 1.0);
		orientation = true;
	}
	else if ((dot1 > dot3) && !(dot1 > dot2)) 
	{
		// printf("2 ] ");
		u = fmod(hit->p.x / SQUARE, 1.0);
		v = fmod(hit->p.y / SQUARE, 1.0);
		orientation = true;
	}
	else //if (!(dot1 > dot3) && (dot1 > dot2))
	{
		// res1 = dot_product(plane->vect, create_vector(1, 0, 0));
		// res2 = dot_product(plane->vect, create_vector(0, 0, 1));
		// printf("1 ] %f\n", res1);
		// printf("2 ] ");
		u = fmod(hit->p.y / SQUARE, 1.0);
		v = fmod(hit->p.z / SQUARE, 1.0);
		orientation = false;
		// return error;
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

    if (plane->tex.data == NULL || plane->checker == false)
    {
        hit->rgb = plane->rgb;
        return;
    }
    hit->rgb = tex_color_plane(plane, hit, pic);
}

void	plane_checker(t_hitinfo *hit, t_plane *plane)
{
	int	square_x;
	int	square_y;
	int	square_z;

	if (plane->checker == false)
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
		hit->rgb = extract_color( 0, 0 , 0);
}

void	plane_bump(t_hitinfo *hit, t_plane *plane)
{
	t_rgb	normal_color;
	t_vect	color_vect;
	t_vect	delta;

	if (plane->tex_norm.data == NULL || plane->checker == false)
    {
        return;
    }

	normal_color = tex_color(hit, plane->tex_norm);
	color_vect = rgb_to_vect(normal_color);
	delta = sub_vect(scale_down(color_vect, 127.5f), create_vector(1.0, 1.0, 1.0));
	hit->normal = normalize(delta);
}
