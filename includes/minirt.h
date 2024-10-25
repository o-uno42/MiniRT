/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:59:39 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/10/22 18:55:27 by tjuvan           ###   ########.fr       */
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
void	sphere_init(t_data *data, char *line);
void	plane_init(t_data *data, char *line);

float	scale(float point, float max_dimention);

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
t_vect	normalize(t_vect v_orig);
int		interpolate_color(int color1, int color2, float ratio);
// MATH UTILS
int		square(float i);
double	ft_atol(const char *nptr);
float	max_nb(float nb1, float nb2);
float	ratio(float nb1, float nb2);


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

#endif
