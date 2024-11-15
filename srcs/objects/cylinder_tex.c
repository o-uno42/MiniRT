/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:19:49 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/15 17:30:23 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void cap_texture(t_hitinfo *hit, t_cylinder *cyl)
{
    if (cyl->tex.data == NULL || cyl->checker == false)
    {
        hit->rgb = cyl->rgb;
        return;
    }
    hit->rgb = tex_color(hit, cyl->tex);
}

void	cap_bump(t_hitinfo *hit, t_cylinder *cyl)
{
	t_rgb	normal_color;
	t_vect	color_vect;
	t_vect	delta;

	if (cyl->tex_normal.data == NULL || cyl->checker == false)
    {
        return;
    }
	normal_color = tex_color(hit, cyl->tex_normal);
	color_vect = rgb_to_vect(normal_color);
	delta = sub_vect(scale_down(color_vect, 127.5f), create_vector(1.0, 1.0, 1.0));
	hit->normal = normalize(delta);
}

void	checker_cyl(t_hitinfo *hit, t_cylinder *cyl)
{
	if (cyl->checker == false)
	{
		hit->rgb = cyl->rgb;
		return ;
	}

	float theta = atan2(hit->p.z, hit->p.x);
	float height = hit->p.y - cyl->p2.y;

	int square_theta = floor(theta  / ANGLE_SIZE);
	int square_height = floor(height * cyl->height * 2 / SQUARE);

	if ((square_theta + square_height) % 2 == 0)
		hit->rgb = cyl->rgb;
	else
		hit->rgb = extract_color(0, 0, 0);
}

t_rgb	tex_cyl_color(t_hitinfo *hit, t_picture pic, t_cylinder *cyl)
{
	t_rgb	final;
	float	theta;
	float	height;
	float	square_theta;
	float	square_height;
	int		tex_theta;
	int		tex_height;

	theta = atan2(hit->p.z, hit->p.x);
	height = hit->p.y - cyl->p2.y;

	square_theta = fmod(theta  / ANGLE_SIZE, 1.0);
	square_height = fmod(height * cyl->height * 2 / SQUARE, 1.0);
	if (square_theta < 0)
		square_theta += 1.0;
	if (square_height < 0)
		square_height += 1.0;
	tex_theta = (int)(square_theta * pic.w);
	tex_height = (int)(square_height * pic.h);
    int color_offset = tex_height * pic.line_len + tex_theta * (pic.bpp / 8);
    int color = *(int *)(pic.data + color_offset);
	final = extract_color_from_int(color);
	return (final);
}

void	tex_cyl(t_hitinfo *hit, t_cylinder *cyl)
{
	if (cyl->checker == false || cyl->tex.data == NULL)
	{
		hit->rgb = cyl->rgb;
		return ;
	}
	hit->rgb = tex_cyl_color(hit, cyl->tex, cyl);
}

void	cyl_bump(t_hitinfo *hit, t_cylinder *cyl)
{

	t_rgb	normal_color;
	t_vect	color_vect;
	t_vect	delta;

	if (cyl->tex_normal.data == NULL || cyl->checker == false)
    {
        return;
    }
	normal_color = tex_cyl_color(hit, cyl->tex_normal, cyl);
	color_vect = rgb_to_vect(normal_color);
	delta = sub_vect(scale_down(color_vect, 127.5f), create_vector(1.0, 1.0, 1.0));
	hit->normal = normalize(delta);
}


