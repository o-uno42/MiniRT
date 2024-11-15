/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:47:37 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/15 14:09:35 by tjuvan           ###   ########.fr       */
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

//formula : data->plane.vect.x * (camera_ray.dir.x - data->plane.pos.x) + data->plane.vect.y * (camera_ray.dir.y - data->plane.pos.y)  + data->plane.vect.z * (camera_ray.dir.z - data->plane.pos.z);
bool render_plane(t_ray camera_ray, t_plane *plane, t_hitinfo *hit)
{
    float visibility;
	float t;
	
	visibility = dot_product(plane->vect, camera_ray.dir);
	
	if (visibility == 0)
        return (false);

	
	t = dot_product(plane->vect, sub_vect(plane->pos, camera_ray.pos)) / visibility;
    // float D = -(dot_product(plane->vect, plane->pos));

    // t = -(D + dot_product(plane->vect, camera_ray.pos)) / visibility;

	/* hit->normal = plane->vect; */
	if( t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, t));
		hit->normal = plane->vect;
		hit->is_outside = true;
		hit->rgb = plane->rgb;
		/* plane_checker(hit, plane); */
		plane_texture(hit, plane, plane->tex);
		plane_bump(hit, plane);
		/* hit->rgb = plane->rgb; */
		/* printf("hit->t plane: %f\t t plane: %f\n", hit->t, t); */
	}

    return (t);
}
