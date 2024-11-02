/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:59:39 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/10/29 17:58:06 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minirt_H
# define minirt_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <float.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "structs.h"

//ERRORS
void	print_error(char *message);

//	RENDER
int    render(t_data *data);

// RENDER INITS
void    ambient_init(t_data *data, char *line);
void	camera_init(t_data *data, char *line);
void	light_init(t_data *data, char *line);
void	sphere_init(t_data *data, char *line, int nb_spheres, int i);
void	plane_init(t_data *data, char *line, int nb_planes, int i);
float	scale(float point, float max_dimension);

//	WINDOW MANAGEMENT
int	keys(int keysym, t_data *map);
int	esc_x(t_data *data);

//	PARSING
void	parsing(int fd, t_data *data);
void    movement(t_data *data);

// VECTOR UTILS
t_vect 	sum_vect(t_vect pos_1, t_vect pos_2);
t_vect	sub_vect(t_vect pos_1, t_vect pos_2);
float	dot_product(t_vect pos_1, t_vect pos_2);
t_vect	cross_product(t_vect a, t_vect b);
t_vect	normalize(t_vect v_orig);
float	magnitude(t_vect v);
t_vect	create_vector(float x, float y, float z);
int		interpolate_color(int color1, int color2, float ratio);
// MATH UTILS
int		square(float i);
double	ft_atol(const char *nptr);
float	max_nb(float nb1, float nb2);
float	ratio(float nb1, float nb2);
void	swap(float *a, float *b);

bool solve_quadratic(const float a, const float b, const float c, float *x0, float *x1);
// DEBUG UTILS
void	print_sphere(t_sphere sphere);
void	print_camera(t_camera camera);
void	print_ray(t_ray ray);
void	print_rgb(t_rgb color);
void	print_vect(t_vect vectr);

//SPLIT
char	**ft_split_rt(char const *s, char c);

//SAFE FT
void    *safe_malloc(size_t size);

//COLOR CREATION
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

// RAYS
t_ray    camera_rays(int x, int y, t_data *data);
t_ray    *light_rays(t_data *data);

//COLOR
int     create_color(t_rgb rgb, t_ambient ambient);

//LIGHT
bool    light_intersect(t_data *data, t_ray *light, int index);

#endif
