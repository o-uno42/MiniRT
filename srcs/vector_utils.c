/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:25:00 by tjuvan            #+#    #+#             */
/*   Updated: 2024/10/29 17:57:26 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vect sum_vect(t_vect pos_1, t_vect pos_2)
{
    t_vect res;
    res.x = pos_1.x + pos_2.x;
    res.y = pos_1.y + pos_2.y;
    res.z = pos_1.z + pos_2.z;

    return (res);
}

t_vect	sub_vect(t_vect pos_1, t_vect pos_2)
{
	t_vect	res;

	res.x = pos_1.x - pos_2.x;
	res.y = pos_1.y - pos_2.y;
	res.z = pos_1.z - pos_2.z;
	return (res);
}


t_vect	mult_vect(t_vect pos_1, t_vect pos_2)
{
	t_vect	res;

	res.x = pos_1.x * pos_2.x;
	res.y = pos_1.y * pos_2.y;
	res.z = pos_1.z * pos_2.z;
	return (res);
}

t_vect scale_vector(t_vect vect, float i)
{
    t_vect res;

    res.x = vect.x * i;
    res.y = vect.y * i;
    res.z = vect.z * i;
    return (res);
}

t_vect	normalize(t_vect v_orig)
{
	float	length;
	t_vect	res;

	length = sqrt(v_orig.x * v_orig.x + v_orig.y * v_orig.y + v_orig.z * v_orig.z);
	res.x = v_orig.x / length;
	res.y = v_orig.y / length;
	res.z = v_orig.z / length;
	return (res);
}

float	dot_product(t_vect pos_1, t_vect pos_2)
{
	return ((pos_1.x * pos_2.x) + (pos_1.y * pos_2.y) + (pos_1.z * pos_2.z));
}

t_vect	cross_product(t_vect a, t_vect b)
{
	t_vect	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

inline float	magnitude(t_vect v)
{
	return (sqrt(square(v.x) + square(v.y) + square(v.z)));
}

inline	t_vect	create_vector(float x, float y, float z)
{
	t_vect res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}


int	interpolate_color(int color1, int color2, float ratio)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = (int)(get_t(color1) * (1 - ratio) + get_t(color2) * ratio);
	r = (int)(get_r(color1) * (1 - ratio) + get_r(color2) * ratio);
	g = (int)(get_g(color1) * (1 - ratio) + get_g(color2) * ratio);
	b = (int)(get_b(color1) * (1 - ratio) + get_b(color2) * ratio);
	return (create_trgb(t, r, g, b));
}
