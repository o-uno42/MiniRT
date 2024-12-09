#include "../../includes/minirt.h"

static bool	cone_end_shadow(t_hitinfo *hit, t_ray ray, t_cone *cone, POINT *res)
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

static t_vect	cone_normal_shadow(t_hitinfo *hit, t_cone *cone)
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
	{
		pdelta = scale_vect(cone->dir, scalar);
		pdelta = scale_vect(pdelta, -1);
	}
	axisp = sum_vect(cone->pos, pdelta);
	normal = normalize(sub_vect(hit->p, axisp));
	return (normal);
}

static bool	hit_cone_shadow(t_hitinfo *hit, float t, t_ray ray, t_cone *cone)
{

	float prev_hit;
	POINT	prev;
	POINT	res;
	
	prev_hit = hit->t;
	prev = hit->p;
	if (t >= hit->t)
		return false;
	hit->t = t;
	hit->p = sum_vect(ray.pos, scale_vect(ray.dir, t));
	if(!cone_end_shadow(hit, ray, cone, &res))
	{
		hit->t = prev_hit;
		hit->p = prev;
		return true;
	}
	hit->rgb = cone->rgb;
	hit->normal = normalize(cone->pos);
	hit->normal = cone_normal_shadow(hit, cone);
	// hit->normal = scale_vect(cone_normal_shadow(hit, cone), -1);
	return false;
}

static bool	hit_cone_shadow_reverse(t_hitinfo *hit, float t, t_ray ray, t_cone *cone)
{

	float prev_hit;
	POINT	prev;
	POINT	res;
	
	prev_hit = hit->t;
	prev = hit->p;
	if (t >= hit->t)
		return false;
	hit->t = t;
	hit->p = sum_vect(ray.pos, scale_vect(ray.dir, t));
	if(!cone_end_shadow(hit, ray, cone, &res))
	{
		hit->t = prev_hit;
		hit->p = prev;
		return true;
	}
	hit->rgb = cone->rgb;
	hit->normal = normalize(cone->pos);
	// hit->normal = cone_normal_shadow(hit, cone);
	hit->normal = scale_vect(cone_normal_shadow(hit, cone), -1);
	return false;
}

bool	render_cone_shadow(t_ray ray, t_data *data, t_cone *cone, t_hitinfo *hit)
{
	float	t1;
	float	t2;
	t_vect	oc;
	t_vect	Acomp;
	float	Acomp2;
	float	Bcomp;
	float	Bcomp2;
	float	Ccomp;
	float	Ccomp2;
	float	cos_square;
	float	sin_square;

	bool	side;

	side = false;
	
	data = data;
	oc = sub_vect(ray.pos, cone->pos);
	cos_square = cos(cone->theta_r) * cos(cone->theta_r);
	sin_square = sin(cone->theta_r) * sin(cone->theta_r);
	
	Acomp = sub_vect(ray.dir, scale_vect(cone->dir, dot_product(ray.dir, cone->dir)));
	Acomp2 = sin_square * dot_product(ray.dir, cone->dir) * dot_product(ray.dir, cone->dir);
	data->a = cos_square * dot_product(Acomp, Acomp) - Acomp2;

	Bcomp = dot_product(sub_vect(ray.dir, scale_vect(cone->dir, dot_product(ray.dir, cone->dir))), sub_vect(oc, scale_vect(cone->dir, dot_product(oc, cone->dir))));
	Bcomp2 = dot_product(ray.dir, cone->dir) * dot_product(oc, cone->dir);
	data->b = (2 * cos_square * Bcomp) - (2 * sin_square * Bcomp2);

	Ccomp = dot_product(sub_vect(oc, scale_vect(cone->dir, dot_product(oc, cone->dir))), sub_vect(oc, scale_vect(cone->dir, dot_product(oc, cone->dir))));
	Ccomp2 = sin_square * dot_product(oc, cone->dir) * dot_product(oc, cone->dir);
	data->c = cos_square * Ccomp - Ccomp2;
	if (solve_quadratic(data, &t1, &t2))
	{
		if (t1 > 0.0003 && t1 < hit->t)
		{
			side = true;
			hit_cone_shadow(hit, t1, ray, cone);
			return (true);
		}
		else if (t2 > 0.0003 && t2 < hit->t)
		{
			// printf("l");
			side = true;
			hit_cone_shadow_reverse(hit, t2, ray, cone);
			return (true);
		}
	}
	if(caps_cone(ray, cone, hit))
	{
		t1 = FLT_MAX;
		hit_cone_shadow(hit, t1, ray, cone);
		t2 = FLT_MAX;
		hit_cone_shadow(hit, t2, ray, cone);
		return (true);
	}
	side = side;

	return (false);
}
