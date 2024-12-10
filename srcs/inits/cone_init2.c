/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:10:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/12/10 16:11:59 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	top_bottom_cone(POINT *p1, POINT *p2, t_cone cone)
{
	*p1 = sum_vect(cone.pos, scale_vect(cone.dir, cone.height / 2));
	*p2 = sum_vect(cone.pos, scale_vect(cone.dir, -cone.height / 2));
}

void	cone_angle(t_cone *cone)
{
	float	angle;

	angle = atan2((*cone).radius, (*cone).height / 2);
	(*cone).theta_r = angle;
	(*cone).theta_d = angle * (180 / M_PI);
}
