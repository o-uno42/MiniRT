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

void plane_texture(t_hitinfo *hit, t_plane *plane, t_picture pic)
{

    if (plane->tex.data == NULL || plane->checker == false)
    {
        hit->rgb = plane->rgb;
        return;
    }
    hit->rgb = tex_color(hit, pic);
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
