/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:25:00 by tjuvan            #+#    #+#             */
/*   Updated: 2024/10/20 18:30:14 by tjuvan           ###   ########.fr       */
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

float	dot_product(t_vect pos_1, t_vect pos_2)
{
	return ((pos_1.x * pos_2.x) + (pos_1.y * pos_2.y) + (pos_1.z * pos_2.z));
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
