/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:38:36 by tjuvan            #+#    #+#             */
/*   Updated: 2024/10/28 15:30:20 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

inline int	square(float i)
{
	return (i * i);
}

double	ft_atol_sign(const char *nptr, int i, double s)
{
	double	num;
	double	num2;
	double	pos;

	num = 0;
	num2 = 0;
	pos = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num *= 10;
		num += (nptr[i] - 48);
		i++;
	}
	if (nptr[i] == '.')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num2 *= 10;
		num2 += (nptr[i] - 48);
		pos *= 10;
		i++;
	}
	return ((num + (num2 / pos)) * s);
}

double	ft_atol(const char *nptr)
{
	int		i;
	double	s;
	double	res;

	i = 0;
	s = 1;
	if (!(*nptr) || !nptr)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	res = ft_atol_sign(nptr, i, s);
	return(res);
}

inline float	max_nb(float nb1, float nb2)
{
	if (nb1 >= nb2) 
		return (nb1);
	return (nb2);
}

inline float	ratio(float nb1, float nb2)
{
	if (nb1 >= nb2) 
		return (nb1 / nb2);
	return (nb2 / nb1);
}

inline	void	swap(float *a, float *b)
{
	float c;
	
	c = *a;
	*a = *b;
	*b = c;
}



