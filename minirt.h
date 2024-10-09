/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:59:39 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/08/30 14:32:16 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minirt_H
# define minirt_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

# define BLACK   0x000000

typedef struct s_ray
{
	double	camera_pos;
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	wall_dist;
	int		line_height;
	int		start;
	int		end;
}			t_ray;

typedef struct s_player
{
	char	dir;
	int		moved;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_x;
	int		move_y;
	int		rotate;
}				t_player;

typedef struct s_ambient
{
	float		ratio;
	int			rgb_1;
	int			rgb_2;
	int			rgb_3;
}				t_ambient;

typedef struct s_camera
{
	float		x;
	float		y;
	float		z;
}				t_camera;

typedef struct s_light
{
	float		x;
	float		y;
	float		z;
	int			rgb_1;
	int			rgb_2;
	int			rgb_3;
}				t_light;

typedef struct s_sphere
{
	float		x;
	float		y;
	float		z;
	float		diameter;
	int			rgb_1;
	int			rgb_2;
	int			rgb_3;
}				t_sphere;


typedef struct s_img
{
	void	*img_ptr;
	char	*pix_ptr;
	int		bpp;
	int		endian;
	int		line_len;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_img		img;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	// void		*ptr;
	// void		*win;
	// int			height;
	// int			width;
	// t_player	player;
	// t_ray		ray;
	// t_map		map;
	// t_img		img;
}			t_data;


//	RENDER
int    render(t_data *data);
void    ambient_init(t_data *data, char *line);


//	WINDOW MANAGEMENT
int	keys(int keysym, t_data *map);
int	esc_x(t_data *data);

//	PARSING
void	parsing(int fd, t_data *data);
void    movement(t_data *data);

//SPLIT
char	**ft_split_rt(char const *s, char c);

//SAFE FT
void    *safe_malloc(size_t size);
#endif