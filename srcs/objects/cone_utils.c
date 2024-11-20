/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:31:07 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/17 16:43:37 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


void	caps_hit(t_cone *cone, t_hitinfo *hit, POINT p, float t)
{
	hit->p = p;
	hit->t = t;
	hit->rgb = cone->rgb;
}

bool	caps_cone(t_ray ray, t_cone *cone, t_hitinfo *hit)
{
	float	visibility;
	float	visibility2;
	float	chosen_t;
	POINT	p;
	POINT	pcenter;
	t_vect	pdelt;
	t_vect	normal;

	visibility = dot_product(cone->dir, ray.dir);
	visibility2 = dot_product(scale_vect(cone->dir, -1), ray.dir);
	if (visibility <= 0 && visibility2 <= 0)
		return (false);
	float t = dot_product(cone->dir, sub_vect(cone->p1, ray.pos)) / visibility;
	float t2 = dot_product(scale_vect(cone->dir, -1), sub_vect(cone->p2, ray.pos)) / visibility2;

	if (t2 > 0 && (t <= 0 || t > t2))
	{
		chosen_t = t2;
		normal = scale_vect(cone->dir, -1);
		pcenter = cone->p2;
	}
	else if (t > 0 && (t2 <= 0 || t2 > t))
	{
		chosen_t = t;
		pcenter = cone->p1;
		normal = cone->dir;

	}
	else
		return (false);
	p = sum_vect(ray.pos, scale_vect(ray.dir, chosen_t));
	pdelt = sub_vect(p, pcenter);
	if (magnitude(pdelt) <= cone->radius && chosen_t < hit->t)
	{
		hit->normal = normal;
		caps_hit(cone, hit, p, chosen_t); 
		return (true);
	}	
	return (false);
}
