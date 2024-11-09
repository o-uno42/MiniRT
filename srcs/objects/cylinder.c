/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:44:53 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/09 13:45:54 by tjuvan           ###   ########.fr       */
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
	hit->rgb = cylinder->rgb;
	hit->normal = normalize(sub_vect(hit->p, res));
}

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

	visibility = dot_product(cylinder->dir, camera_ray.dir);
	visibility2 = dot_product(scale_vect(cylinder->dir, -1), camera_ray.dir);
	if (visibility <= 0 && visibility2 <= 0)
		return (false);

	float t = dot_product(cylinder->dir, sub_vect(cylinder->p1, camera_ray.pos)) / visibility;
	float t2 = dot_product(scale_vect(cylinder->dir, -1), sub_vect(cylinder->p2, camera_ray.pos)) / visibility2;

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
		if (magnitude(pdelt) > cylinder->radius - 0.07 && magnitude(pdelt) <= cylinder->radius)
			hit->rgb = extract_color(0, 0, 0);
		return (true);
	}	

	return (false);
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
		intersect1 = FLT_MAX;
		calc_hit_cyl(hit, intersect1, camera_ray, cylinder);
		return (true);
	}
	return (true);
}

