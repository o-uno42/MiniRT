#include "../../includes/minirt.h"

static bool	caps_2(t_ray camera_ray, t_cylinder *cylinder, t_hitinfo *hit)
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
	if (chosen_t > hit->t)
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

static bool cyl_end_2(t_hitinfo *hit, t_ray camera_ray, t_cylinder *cylinder, POINT *res)
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

static bool	calc_hit_cyl_2(t_hitinfo *hit, float intersect, t_ray camera_ray, t_cylinder *cylinder)
{
	float prev_hit;
	POINT	prev;
	POINT	res;

	prev_hit = hit->t;
	prev = hit->p;
	if (intersect >= hit->t + 0.0003)
		return false;
	hit->t = intersect;
	hit->p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, intersect));
	if(!cyl_end_2(hit, camera_ray, cylinder, &res))
	{
		hit->t = prev_hit;
		hit->p = prev;
		return false;
	}
	hit->normal = normalize(sub_vect(hit->p, res));
	checker_cyl(hit, cylinder);
	tex_cyl(hit, cylinder);
	cyl_bump(hit, cylinder);
	return true;
}

bool	render_cylinder_shadow(t_ray shadow_ray, t_cylinder *cylinder, t_hitinfo *hit)
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

	pdelt = sub_vect(shadow_ray.pos, cylinder->pos);
	comp = sub_vect(shadow_ray.dir, scale_vect(cylinder->dir, dot_product(shadow_ray.dir, cylinder->dir)));
	a = dot_product(comp, comp);
	b1 = sub_vect(pdelt, scale_vect(cylinder->dir, dot_product(pdelt, cylinder->dir)));
	b = 2 * dot_product(comp, b1); 
	c1 = sub_vect(pdelt, scale_vect(cylinder->dir, dot_product(pdelt, cylinder->dir)));
	c = dot_product(c1, c1) - cylinder->radius * cylinder->radius;
	if(solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0.0001 && intersect1 < hit->t)
		{
			if(calc_hit_cyl_2(hit, intersect1, shadow_ray, cylinder))
			return (true);
		}
	}
	if (caps_2(shadow_ray, cylinder, hit))
		return (true);
	return (false);
}
