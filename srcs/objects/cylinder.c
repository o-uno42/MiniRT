/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:44:53 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/16 20:26:28 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

 
bool cyl_end(t_hitinfo *hit, t_ray camera_ray, t_cylinder *cylinder, POINT *res)
{
	t_vect	hypotenuse;
	t_vect	proj;
	t_vect	p_to_res;
	float	proj_len;

	camera_ray = camera_ray;
	hypotenuse = sub_vect(hit->p, cylinder->pos);
	proj = scale_vect(cylinder->dir, dot_product(hypotenuse, cylinder->dir));
	*res = sum_vect(cylinder->pos, proj);
	p_to_res = sub_vect(*res, cylinder->p2);
	proj_len = dot_product(p_to_res, cylinder->dir);
	if (proj_len >= 0 && proj_len <= cylinder->height)
		return (true);
	else
		return (false);
}

void	calc_hit_cyl(t_hitinfo *hit, float intersect, t_ray camera_ray, t_cylinder *cylinder)
{
	float prev_hit;
	POINT	prev;
	POINT	res;
	
	prev_hit = hit->t;
	prev = hit->p;
	if (intersect >= hit->t)
		return ;
	hit->t = intersect;
	hit->p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, intersect));
	if(!cyl_end(hit, camera_ray, cylinder, &res))
	{
		hit->t = prev_hit;
		hit->p = prev;
		return;
	}
	hit->normal = normalize(sub_vect(hit->p, res));
	checker_cyl(hit, cylinder);
	tex_cyl(hit, cylinder);
	cyl_bump(hit, cylinder);
}

bool	render_cylinder(t_ray camera_ray, t_data *data, t_cylinder *cylinder, t_hitinfo *hit)
{
	float	a;
	float	b;
	float	c;
	float	intersect1;
	float	intersect2;
	t_vect	comp;
	t_vect	pdelt;
	t_vect	b1;
	t_vect	c1;

	data=data;
	pdelt = sub_vect(camera_ray.pos, cylinder->pos);
	comp = sub_vect(camera_ray.dir, scale_vect(cylinder->dir, dot_product(camera_ray.dir, cylinder->dir)));
	a = dot_product(comp, comp);
	b1 = sub_vect(pdelt, scale_vect(cylinder->dir, dot_product(pdelt, cylinder->dir)));
	b = 2 * dot_product(comp, b1); 
	c1 = sub_vect(pdelt, scale_vect(cylinder->dir, dot_product(pdelt, cylinder->dir)));
	c = dot_product(c1, c1) - cylinder->radius * cylinder->radius;
	if(solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0)
		{
			calc_hit_cyl(hit, intersect1, camera_ray, cylinder);
			/* return (true); */
		}
	}
	if(!caps(camera_ray, cylinder, hit))
	{
		/* intersect1 = FLT_MAX; */
		/* calc_hit_cyl(hit, intersect1, camera_ray, cylinder); */
		/* return (true); */
	}
	return (false);
}

