/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:29:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/09 17:35:59 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


bool	render_hyperboloid(t_ray camera_ray, t_data *data, t_hyperboloid *hyperboloid, t_hitinfo *hit)
{
	float	t;
	float	t2;
	float	A;
	float	B;
	float	C;
	float	a;
	float	b;
	float	c;
	t_vect	oc;
	t_vect	comp_dir;
	t_vect	comp_delta;

	a = hyperboloid->a;
	b = hyperboloid->b;
	c = hyperboloid->c;
	oc = sub_vect(camera_ray.pos, hyperboloid->pos);
	comp_dir = sub_vect(camera_ray.dir, scale_vect(hyperboloid->dir, dot_product(camera_ray.dir, hyperboloid->dir)));
	comp_delta = sub_vect(oc, scale_vect(hyperboloid->dir, dot_product(oc, hyperboloid->dir)));

	/* A = (comp_dir.x * comp_dir.x) / (a * a) + (comp_dir.y * comp_dir.y) / (b * b) - (comp_dir.z * comp_dir.z) / (c * c); */
	/* B = 2 * ((comp_dir.x * comp_delta.x) / (a * a) + (comp_dir.y * comp_delta.y) / (b * b) - (comp_dir.z * comp_delta.z) / (c * c)); */
	/* C = (comp_delta.x * comp_delta.x) / (a * a) + (comp_delta.y * comp_delta.y) / (b * b) - (comp_delta.z * comp_delta.z) / (c * c) - 1; */
	A = (comp_dir.x * comp_dir.x) / (a * a) + (comp_dir.y * comp_dir.y) / (b * b) - (comp_dir.z * comp_dir.z) / (c * c);
	B = 2 * ((comp_dir.x * comp_delta.x) / (a * a) + (comp_dir.y * comp_delta.y) / (b * b) - (comp_dir.z * comp_delta.z) / (c * c));
	C = (comp_delta.x * comp_delta.x) / (a * a) + (comp_delta.y * comp_delta.y) / (b * b) - (comp_delta.z * comp_delta.z) / (c * c) - 1;
	if (solve_quadratic(A, B, C, &t, &t2))
	{
		if (t > 0 && t < hit->t)
		{
			hit->t = t;
			hit->rgb = hyperboloid->rgb;
			return (true);
		}
	}
	data = data;
	return (false);
}
