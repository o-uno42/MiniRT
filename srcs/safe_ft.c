/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:27 by thiew             #+#    #+#             */
/*   Updated: 2024/12/10 16:39:05 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
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

bool	check_extension(char *file_name)
{
	char	**check;
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

bool	invalid_params(char **params, int valid_params, t_data *data)
{
	int	i;

	i = mtx_count(params);
	printf("count params is: %d, at %s\n", i, params[0]);
	if (i < valid_params)
	{
		write(2, "invalid params at <", 19);
		write(2, params[0], ft_strlen(params[0]));
		write(2, ">\n", 2);
		free_mtx(params);
		data->invalid = true;
		return (true);
	}
	return (false);
}

bool	invalid_parts(char ***parts, int valid_parts, t_data *data,
		char *parent)
{
	int	i;

	*parts = ft_split(parent, ',');
	i = mtx_count(*parts);
	if (i != valid_parts)
	{
		write(2, "invalid parts at <", 19);
		write(2, parent, ft_strlen(parent));
		write(2, ">\n", 2);
		free_mtx(*parts);
		*parts = NULL;
		data->invalid = true;
		return (true);
	}
	return (false);
}
