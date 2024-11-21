/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:17 by thiew             #+#    #+#             */
/*   Updated: 2024/11/14 19:45:47 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*ft_strdup_new(char *str, int len)
{
	char	*array;
	int		count;

	if (!str || !len)
		return (NULL);
	count = 0;
	array = (char *)malloc((len + 1)* sizeof(char));
	if (!array)
		return (NULL);
	while (count < len)
	{
		array[count] = str[count];
		count++;
	}
	array[count] = '\0';
	return (array);
}

static char	*extract_line(char **buff)
{
	int		n_pos;
	char	*line;
	char	*str;

	if (!*buff)
		return (NULL);
	str = *buff;
	n_pos = 0;
	while (str[n_pos] && str[n_pos] != '\n')
		n_pos++;
	if (str[n_pos] == '\n')
		n_pos++;
	line = ft_strdup_new(str, n_pos);
	if (!line)
		return (NULL);
	*buff = ft_strdup_new(str + n_pos, ft_strlen(str + n_pos));
	if (str)
		free(str);
	str = (NULL);
	return (line);
}

static char	*get_next_line(int fd)
{
	static char	*buff;
	char		*result;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buff), buff = NULL, NULL);
	if (ft_strchr(buff, '\n'))
		return (extract_line(&buff));
	result = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!result)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, result, BUFFER_SIZE);
		result[bytes] = '\0';
		buff = ft_strjoin(buff, result);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (result)
		free(result);
	result = (NULL);
	return (extract_line(&buff));
}

int	check_line(char *line)
{
	line = line;
	return (0);
}

void	prefix(char *line, t_data *data, int *nb_objs, int *nb_pics, int *nb_lights)
{
	int i;

	i = 0;
	data = data;
	while (line[i])
	{
		if (line[i] == ' ')
			break;
		i++;
	}
	if (ft_strncmp("A", line, i) == 0)
		ambient_init(data, line);
	else if (ft_strncmp("C", line, i) == 0)
		camera_init(data, line);
	else if (ft_strncmp("L", line, i) == 0)
	{
		lights_init(data, line, (*nb_lights));
		(*nb_lights)++;
	}
		// light_init(data, line);
	else if (ft_strncmp("l", line, i) == 0)
	{
		lights_init(data, line, (*nb_lights));
		(*nb_lights)++;
	}
	else if (ft_strncmp("sp", line, i) == 0)
	{
		sphere_init(data, line, (*nb_objs));
		(*nb_objs)++;
	}
	else if (ft_strncmp("pl", line, i) == 0)
	{
		plane_init(data, line, (*nb_objs));
		(*nb_objs)++;
	}
	else if (ft_strncmp("cy", line, i) == 0)
	{
		cylinder_init(data, line, (*nb_objs));
		(*nb_objs)++;
	}
	else if (ft_strncmp("hy", line, i) == 0)
	{
		hyperboloid_init(data, line, (*nb_objs));
		(*nb_objs)++;
	}
	else if (ft_strncmp("cn", line, i) == 0)
	{
		cone_init(data, line, *nb_objs);
		(*nb_objs)++;
	}
	else if (ft_strncmp("pic", line ,i) == 0)
	{
		pic_init(data, line, *nb_pics);
		(*nb_pics)++;
	}
}

void	parsing(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		nb_objects;
	int		nb_pics;
	int		nb_lights;

	i = 0;
	nb_objects = 0;
	nb_pics = 0;
	nb_lights = 0;
	data->pic_idx = 0;

	while((line = get_next_line(fd)) !=NULL)
	{
		check_line(line);
		prefix(line, data, &nb_objects, &nb_pics, &nb_lights);
		// free(line);
		i++;
	}
	data->obj[nb_objects].type_obj = END;
	data->nb_lights = nb_lights;
	print_all_obj(data);
}
