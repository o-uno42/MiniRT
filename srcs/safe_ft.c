/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:27 by thiew             #+#    #+#             */
/*   Updated: 2024/12/07 14:49:12 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		perror("Malloc failed");
		exit (EXIT_FAILURE);
	}
	return (ptr);
}

char	*join_wrapper(const char *s1, const char *s2, int free_which)
{
	char	*result;

	result = ft_strjoin(s1, s2);

	if (free_which == 1)
		free((char *)s1);
	else if (free_which == 2)
		free((char *)s2);
	else if (free_which == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
	return (result);
}

bool	check_extension( char *file_name)
{
	char 	**check;
	bool	is_extension;
	int		i;

	i = 0;
	is_extension = false;
	check = ft_split(file_name, '.');
	while (check[i])
		i++;
	if (i != 2)
		is_extension = false;
	else if (ft_strncmp(check[1], "rt", 3) == 0)
			is_extension = true;
	free_mtx(check);
	return (is_extension);
}
