/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:17 by thiew             #+#    #+#             */
/*   Updated: 2024/12/09 19:25:14 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	obj_pars(char *line, t_data *data, int i, int *nb_pics)
{
	if (ft_strncmp("sp", line, i) == 0)
	{
		sphere_init(data, line, data->nb_objs);
		data->nb_objs++;
	}
	else if (ft_strncmp("pl", line, i) == 0)
	{
		plane_init(data, line, data->nb_objs);
		data->nb_objs++;
	}
	else if (ft_strncmp("cy", line, i) == 0)
	{
		cylinder_init(data, line, data->nb_objs);
		data->nb_objs++;
	}
	else if (ft_strncmp("cn", line, i) == 0)
	{
		cone_init(data, line, data->nb_objs);
		data->nb_objs++;
	}
	else if (ft_strncmp("pic", line, i) == 0)
	{
		(*nb_pics)++;
		pic_init(data, line, nb_pics);
	}
}

void	amb_camera(char *line, t_data *data, int i)
{
	if (ft_strncmp("A", line, i) == 0)
	{
		data->nb_main++;
		ambient_init(data, line);
	}
	else if (ft_strncmp("C", line, i) == 0)
	{
		data->nb_main++;
		camera_init(data, line);
	}
}

int	prefix(char *line, t_data *data, int *nb_pics)
{
	int			i;
	static int	args;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			break ;
		i++;
	}
	amb_camera(line, data, i);
	if (ft_strncmp("L", line, i) == 0)
	{
		lights_init(data, line, data->nb_lights);
		data->nb_lights++;
		data->nb_main++;
		args++;
	}
	else if (ft_strncmp("l", line, i) == 0)
	{
		lights_init(data, line, data->nb_lights);
		data->nb_lights++;
		args++;
	}
	obj_pars(line, data, i, nb_pics);
	return (args);
}

int	line_parsing(int fd, t_data *data, int *nb_pics)
{
	int		i;
	char	*line;
	bool	first;

	i = 0;
	first = true;
	while (1)
	{
		if (first == false)
			free(line);
		first = false;
		line = get_next_line(fd);
		if (line == NULL)
			return (i);
		line = check_line(line);
		if (line && line[0] != 0)
		{
			i = prefix(line, data, nb_pics);
		}
	}
	free(line);
	return (i);
}

void	parsing(int fd, t_data *data)
{
	int	i;
	int	nb_pics;

	i = 0;
	nb_pics = -1;
	data->nb_objs = 0;
	data->nb_lights = 0;
	data->pic_idx = 0;
	data->nb_main = 0;
	i = line_parsing(fd, data, &nb_pics);
	data->obj[data->nb_objs].type_obj = END;
	data->pic_idx = nb_pics;
	close(fd);
	if (data->invalid == true || data->not_number == true || i == 0)
	{
		mlx_loop_end(data->mlx_ptr);
		clean(data);
		exit(1);
	}
	print_all_obj(data);
}
