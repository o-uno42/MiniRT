/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:58:29 by tjuvan            #+#    #+#             */
/*   Updated: 2024/10/20 19:00:20 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef		STRUCTS_H
# define	STRUCTS_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

#ifndef PI
# define PI 3.1415926535
#endif

# define BLACK   		0x000000
# define WHITE			0xFFFFFF
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define YELLOW			0xFFFF00
# define CYAN			0x00FFFF
# define MAGENTA		0xFF00FF
# define GRAY			0x808080
# define DARK_GRAY		0x404040
# define LIGHT_GRAY		0xC0C0C0
# define ORANGE			0xFFA500
# define PINK			0xFFC0CB
# define PURPLE			0x800080
# define BROWN			0xA52A2A
# define LIME			0xBFFF00
# define OLIVE			0x808000
# define MAROON			0x800000
# define NAVY			0x000080
# define TEAL			0x008080
# define AQUA			0x00FFFF



typedef struct s_vect
{
	float		x;
	float		y;
	float		z;
}				t_vect;
typedef struct s_ray
{
	t_vect	pos;

	t_vect	dir;
}			t_ray;

// typedef struct s_pos
// {
// 	float		x;
// 	float		y;
// 	float		z;
// }				t_pos;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;
// typedef struct s_player
// {
// 	char	dir;
// 	int		moved;
// 	double	pos_x;
// 	double	pos_y;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// 	int		move_x;
// 	int		move_y;
// 	int		rotate;
// }				t_player;

typedef struct s_intersections
{
	t_vect		t0;
	t_vect		t1;
	int			refl_angle;
	int			nb_collision;
}				t_intersections;

typedef struct s_ambient
{
	float		ratio;
	t_rgb		rgb;
}				t_ambient;

typedef struct s_camera
{
	t_vect	pos;

	t_vect	dir;

	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vect		pos;

	float		bright;

	t_rgb		rgb;
}				t_light;

typedef struct s_sphere
{
	t_vect		pos;
	float		diameter;
	float		radius;
	t_rgb		rgb;
}				t_sphere;

typedef struct s_plane
{
	t_vect		pos;
	t_vect		posn;
	t_vect		vect;
	t_rgb		rgb;
}				t_plane;

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
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	// void		*ptr;
	// void		*win;
	// int			height;
	// int			width;
	// t_player	player;
	// t_ray		ray;
	// t_map		map;
	// t_img		img;
}			t_data;

#endif
