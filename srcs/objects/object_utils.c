/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:50:10 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/02 18:22:56 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	swap_objs(t_objs *a, t_objs *b)
{
	t_objs	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	solve_quadratic(const float a, const float b, const float c, float *x0,
		float *x1)
{
	float	discr;
	float	q;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
	{
		*x0 = -0.5 * b / a;
		*x1 = *x0;
	}
	else
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discr));
		else
			q = -0.5 * (b - sqrt(discr));
		*x0 = q / a;
		*x1 = c / q;
	}
	if (*x0 > *x1)
		swap(x0, x1);
	return (true);
}
