/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:17 by thiew             #+#    #+#             */
/*   Updated: 2024/12/07 17:29:58 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*check_line(char *line)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != '#')
		i++;
	if (i == 0)
	{
		free(line);
		return(NULL);
	}
	if (line[i] == 0 && i > 0)
		return (line);
	res = ft_substr(line, 0, i);
	free(line);
	line = ft_strtrim(res, " ");
	free(res);
	if (line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
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
		cone_init(data, line, (*nb_objs));
		(*nb_objs)++;
	}
	else if (ft_strncmp("pic", line ,i) == 0)
	{
		(*nb_pics)++;
		pic_init(data, line, nb_pics);
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
	nb_pics = -1;
	nb_lights = 0;
	data->pic_idx = 0;

	//TODO if some parameter is wrong exit
	// printf("LINES\n");
	while((line = get_next_line(fd)) !=NULL)
	{
		line = check_line(line);
		// printf("%d line: %s, len: %ld \n",i, line, ft_strlen(line));
		if (line && line[0] != 0)
		{
			prefix(line, data, &nb_objects, &nb_pics, &nb_lights);
			free(line);
		}
		i++;
	}
	free(line);
	data->obj[nb_objects].type_obj = END;
	data->nb_lights = nb_lights;
	data->pic_idx = nb_pics;
	close(fd);
	if (data->invalid == true)
	{
		mlx_loop_end(data->mlx_ptr);
		clean(data);
		exit(1);
	}
}
