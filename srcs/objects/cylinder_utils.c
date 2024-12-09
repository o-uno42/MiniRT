/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:26:50 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/09 17:23:27 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	cap_hit(t_cylinder *cylinder, t_hitinfo *hit, POINT p, float t)
{
	hit->p = p;
	hit->t = t;
	hit->rgb = cylinder->rgb;
}

bool	caps(t_ray camera_ray, t_cylinder *cylinder, t_hitinfo *hit)
{
	float	visibility;
	float	visibility2;
	float	chosen_t;
	POINT	p;
	POINT	pcenter;
	t_vect	pdelt;
	t_vect	normal;
	float	t;
	float	t2;

	visibility = dot_product(cylinder->dir, camera_ray.dir);
	visibility2 = dot_product(scale_vect(cylinder->dir, -1), camera_ray.dir);
	if (visibility <= 0 && visibility2 <= 0)
		return (false);
	t = dot_product(cylinder->dir, sub_vect(cylinder->p1, camera_ray.pos))
		/ visibility;
	t2 = dot_product(scale_vect(cylinder->dir, -1), sub_vect(cylinder->p2,
				camera_ray.pos)) / visibility2;
	if (t2 > 0 && (t <= 0 || t > t2))
	{
		chosen_t = t2;
		normal = scale_vect(cylinder->dir, -1);
		pcenter = cylinder->p2;
	}
	else if (t > 0 && (t2 <= 0 || t2 > t))
	{
		chosen_t = t;
		pcenter = cylinder->p1;
		normal = cylinder->dir;
	}
	else
		return (false);
	p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, chosen_t));
	pdelt = sub_vect(p, pcenter);
	if (magnitude(pdelt) <= cylinder->radius && chosen_t < hit->t)
	{
		hit->normal = normal;
		cap_hit(cylinder, hit, p, chosen_t);
		cap_texture(hit, cylinder);
		cap_bump(hit, cylinder);
		return (true);
	}
	return (false);
}
