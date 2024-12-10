/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:36:37 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/10 18:36:39 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect	reflect_vect(t_vect v, t_vect n)
{
	t_vect	dst;

	dst = scale_vect(n, 2 * dot_product(v, n));
	dst = sub_vect(dst, v);
	return (dst);
}

t_rgb	calculate_specular(t_hitinfo *hit, t_vect light_dir, t_ray camera_ray,
		float shininess)
{
	t_vect	reflect;
	t_vect	view_dir;
	float	spec;

	reflect = reflect_vect(hit->normal, light_dir);
	reflect = normalize(reflect);
	view_dir = sub_vect(camera_ray.pos, hit->p);
	view_dir = normalize(view_dir);
	spec = max_nb(0, dot_product(reflect, view_dir));
	spec = pow(spec, shininess);
	return (bri(hit->rgb, spec));
}
