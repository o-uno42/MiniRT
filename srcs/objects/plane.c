/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:47:37 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/15 16:31:54 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minirt.h"

bool render_plane_shit(t_ray camera_ray, t_plane *plane, t_hitinfo *hit)
{
    float visibility;
	float t;
	
	visibility = dot_product(plane->vect,(camera_ray.dir));
	
	if (visibility > 0.0003)
        return (false);

	
	t = dot_product(plane->vect, sub_vect(plane->pos, camera_ray.pos)) / visibility;
    // float D = (dot_product(plane->vect, plane->pos));

    // t = (D + dot_product(plane->vect, camera_ray.pos)) / visibility;

	/* hit->normal = plane->vect; */
	if( t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, t));
		hit->normal = plane->vect;
		hit->is_outside = true;
		hit->rgb = plane->rgb;
		plane_checker(hit, plane);
		plane_texture(hit, plane, plane->tex);
		plane_bump(hit, plane);
		/* hit->rgb = plane->rgb; */
		/* printf("hit->t plane: %f\t t plane: %f\n", hit->t, t); */
	}

    return (t);
}

bool render_plane(t_ray shadow_ray, t_plane *plane, t_hitinfo *hit) {
    float visibility;
    float t;
    float D;

    visibility = dot_product(plane->vect, shadow_ray.dir);

    if (visibility > 0.0003)
        return false;
    t_vect adjusted_normal = plane->vect;
    if (visibility > 0)
        adjusted_normal = scale_vect(plane->vect, -1);
    // else
    //     adjusted_normal = scale_vect(plane->vect, 1);;
    D = -(dot_product(plane->vect, plane->pos));

    t = -(D + dot_product(plane->vect, shadow_ray.pos)) / visibility;
    if (t <= 0.0003 || t >= hit->t)
        return false;
    hit->t = t;
    hit->p = sum_vect(shadow_ray.pos, scale_vect(shadow_ray.dir, t));
    hit->normal = adjusted_normal;
    hit->is_outside = true;
    hit->rgb = plane->rgb;
	plane_checker(hit, plane);
	plane_texture(hit, plane, plane->tex);
	plane_bump(hit, plane);

    return true;
}
