/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:54:51 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/16 23:01:29 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	cone_end(t_hitinfo *hit, t_ray ray, t_cone *cone, POINT *res)
{

	t_vect	hypotenuse;
	t_vect	proj;
	t_vect	p_to_res;
	float	proj_len;

	ray = ray;
	hypotenuse = sub_vect(hit->p, cone->pos);
	proj = scale_vect(cone->dir, dot_product(hypotenuse, cone->dir));
	*res = sum_vect(cone->pos, proj);
	p_to_res = sub_vect(*res, cone->p2);
	proj_len = dot_product(p_to_res, cone->dir);
	if (proj_len >= 0 && proj_len <= cone->height)
		return (true);
	else
		return (false);
}

t_vect	cone_normal(t_hitinfo *hit, t_cone *cone)
{
	t_vect	normal;
	t_vect	pdelta;
	POINT	axisp;
	float	adjacent;
	float	scalar;

	pdelta = sub_vect(cone->pos, hit->p);
	adjacent = magnitude(pdelta);
	scalar = adjacent / cos(cone->theta_r);
	if (dot_product(cone->dir, pdelta) >= 0)
		pdelta = scale_vect(cone->dir, scalar);
	else
		pdelta = scale_vect(cone->dir, -scalar);
	axisp = sum_vect(cone->pos, pdelta);
	normal = normalize(sub_vect(hit->p, axisp));
	return (normal);
}

void	hit_cone(t_hitinfo *hit, float t, t_ray ray, t_cone *cone)
{

	float prev_hit;
	POINT	prev;
	POINT	res;
	
	prev_hit = hit->t;
	prev = hit->p;
	if (t >= hit->t)
		return ;
	hit->t = t;
	hit->p = sum_vect(ray.pos, scale_vect(ray.dir, t));
	if(!cone_end(hit, ray, cone, &res))
	{
		hit->t = prev_hit;
		hit->p = prev;
		return;
	}
	hit->rgb = cone->rgb;
	hit->normal = normalize(cone->pos);
	hit->normal = cone_normal(hit, cone);
	/* hit->normal = scale_vect(cone_normal(hit, cone), -1); */
}

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
	/* float	r; */
	/* float	h; */

	visibility = dot_product(cone->dir, ray.dir);
	visibility2 = dot_product(scale_vect(cone->dir, -1), ray.dir);
	if (visibility <= 0 && visibility2 <= 0)
		return (false);
	/* r = cone->height / 2 * tan(cone->theta_r); */
	/* h = magnitude(sub_vect(cone->p1, cone->pos)); */
	/* printf("radius : %f \t height: %f\t", r, h); */
	/* r = h * tan(cone->theta_r); */
	/* printf("new radius: %f\n", r); */

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

		/* printf("t: %f, t2: %f, p: [%f, %f, %f], pdelt: [%f, %f, %f], radius check: %f\n", t, t2, p.x, p.y, p.z, pdelt.x, pdelt.y, pdelt.z, magnitude(pdelt)); */
		hit->normal = normal;
		caps_hit(cone, hit, p, chosen_t); 
		/* if (magnitude(pdelt) > cone->radius - 0.07 && magnitude(pdelt) <= cone->radius) */
		/* 	hit->rgb = extract_color(0, 0, 0); */
		return (true);
	}	
	return (false);
}

bool	render_cone(t_ray ray, t_data *data, t_cone *cone, t_hitinfo *hit)
{
	float	t1;
	float	t2;
	float	A;
	float	B;
	float	C;
	t_vect	oc;
	t_vect	Acomp;
	float	Acomp2;
	float	Bcomp;
	float	Bcomp2;
	float	Ccomp;
	float	Ccomp2;
	float	cos_square;
	float	sin_square;


	
	data = data;
	oc = sub_vect(ray.pos, cone->pos);
	cos_square = cos(cone->theta_r) * cos(cone->theta_r);
	sin_square = sin(cone->theta_r) * sin(cone->theta_r);
	
	Acomp = sub_vect(ray.dir, scale_vect(cone->dir, dot_product(ray.dir, cone->dir)));
	Acomp2 = sin_square * dot_product(ray.dir, cone->dir) * dot_product(ray.dir, cone->dir);
	A = cos_square * dot_product(Acomp, Acomp) - Acomp2;

	Bcomp = dot_product(sub_vect(ray.dir, scale_vect(cone->dir, dot_product(ray.dir, cone->dir))), sub_vect(oc, scale_vect(cone->dir, dot_product(oc, cone->dir))));
	Bcomp2 = dot_product(ray.dir, cone->dir) * dot_product(oc, cone->dir);
	B = (2 * cos_square * Bcomp) - (2 * sin_square * Bcomp2);

	Ccomp = dot_product(sub_vect(oc, scale_vect(cone->dir, dot_product(oc, cone->dir))), sub_vect(oc, scale_vect(cone->dir, dot_product(oc, cone->dir))));
	Ccomp2 = sin_square * dot_product(oc, cone->dir) * dot_product(oc, cone->dir);
	C = cos_square * Ccomp - Ccomp2;
	if (solve_quadratic(A, B, C, &t1, &t2))
	{
		if (t1 > 0 && t1 < hit->t)
		{
			hit_cone(hit, t1, ray, cone);
			/* return (true); */
		}
	}
	if(!caps_cone(ray, cone, hit))
	{
		t1 = FLT_MAX;
		/* hit_cone(hit, t1, ray, cone); */
		return (true);
	}

	return (false);
}
