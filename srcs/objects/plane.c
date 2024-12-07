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

bool render_plane(t_ray camera_ray, t_plane *plane, t_hitinfo *hit)
{
    float visibility;
	float t;
	
	visibility = dot_product(plane->vect, camera_ray.dir);
	
	if (visibility == 0)
        return (false);

	
	// t = dot_product(plane->vect, sub_vect(plane->pos, camera_ray.pos)) / visibility;
    float D = -(dot_product(plane->vect, plane->pos));

    t = -(D + dot_product(plane->vect, camera_ray.pos)) / visibility;

	/* hit->normal = plane->vect; */
	if(t > 0 && t < hit->t)
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
	else
	{
		hit->normal = scale_vect(hit->normal, -1);
	}
    return (t);
}
