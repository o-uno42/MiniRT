/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:59:39 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/11/21 13:23:03 by tjuvan           ###   ########.fr       */
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

void	my_pixel_put(t_data *data, int x, int y, int color);

//	PARSING
void	parsing(int fd, t_data *data);
void    movement(t_data *data);

// RENDER INITS
void	pic_init(t_data *data, char *line, int nb_pics);
t_hitinfo	init_hit(t_data *data);
void    ambient_init(t_data *data, char *line);
void	camera_init(t_data *data, char *line);
void	light_init(t_data *data, char *line);
void	sphere_init(t_data *data, char *line, int i);
void	plane_init(t_data *data, char *line, int i);
void	cylinder_init(t_data *data, char *line, int i);
void	hyperboloid_init(t_data *data, char *line, int i);
void	cone_init(t_data *data, char *line, int i);
float	scale(float point, float max_dimension);
//	RENDER
int		render(t_data *data);
//	BONUS CHEKER
void	bonus_sphere(t_sphere *sphere, bool light_finished);
void	bonus_plane(t_plane *plane, bool light_finished);
void	bonus_cylinder(t_cylinder *cylinder, bool light_finished);
void	bonus_cone(t_cone *cone, bool light_finished);
//OBJECTS
bool	render_sphere(t_ray camera_ray, t_data *data, t_sphere *sphere, t_hitinfo *hit);
bool	render_cylinder(t_ray camera_ray, t_data *data, t_cylinder *cylinder, t_hitinfo *hit);
bool 	render_plane(t_ray camera_ray, t_plane *plane, t_hitinfo *hit);
bool	render_hyperboloid(t_ray camera_ray, t_data *data, t_hyperboloid *hyperboloid, t_hitinfo *hit);
bool	render_cone(t_ray ray, t_data *data, t_cone *cone, t_hitinfo *hit);
//OBJECT_UTILS
void 	swap_objs(t_objs *a, t_objs *b);
bool 	solve_quadratic(const float a, const float b, const float c, float *x0, float *x1);
void 	plane_texture(t_hitinfo *hit, t_plane *plane, t_picture pic);
//CYLINDER UTILS
void	tex_cyl(t_hitinfo *hit, t_cylinder *cyl);
void	cyl_bump(t_hitinfo *hit, t_cylinder *cyl);
void	checker_cyl(t_hitinfo *hit, t_cylinder *cyl);
void cap_texture(t_hitinfo *hit, t_cylinder *cyl);
void	cap_bump(t_hitinfo *hit, t_cylinder *cyl);
bool	caps(t_ray camera_ray, t_cylinder *cylinder, t_hitinfo *hit);
void	cap_hit(t_cylinder *cylinder, t_hitinfo *hit, POINT p, float t);

//CONE UTILS
bool	caps_cone(t_ray ray, t_cone *cone, t_hitinfo *hit);

//SPHERE UTILS
t_rgb	tex_sphere_color(t_hitinfo *hit, t_picture pic, t_sphere *sphere);
void	sphere_texture(t_hitinfo *hit, t_sphere *sphere);
void	sphere_bump(t_hitinfo *hit, t_sphere *sphere);
//PLANE UTILS
t_rgb	tex_color(t_hitinfo *hit, t_picture pic);
void plane_texture(t_hitinfo *hit, t_plane *plane, t_picture pic);
void	plane_checker(t_hitinfo *hit, t_plane *plane);
void	plane_bump(t_hitinfo *hit, t_plane *plane);

// RAYS
t_ray    camera_rays(int x, int y, t_data *data);
//LIGHT

t_rgb super_light_bonus_intersect(t_data *data, t_ray **light, t_ray camera_ray, t_hitinfo *hit, int x, int y);

// t_rgb light_intersect(t_data *data, t_ray *light, t_ray camera_ray, t_hitinfo *hit,  int x, int y);
t_rgb lights_intersect(t_data *data, t_ray **light, t_ray camera_ray, t_hitinfo *hit,  int x, int y);
t_ray	*light_rays(t_data *data);
t_ambient  darker_ambient(t_ambient ambient, float i);
t_vect reflect(t_vect in, t_vect normal);
t_ray    *reflection_rays(t_data *data, t_hitinfo *hit);
bool reflect_intersect(t_data *data, t_ray *light, t_hitinfo *hit);
bool    specular_intersect(t_data *data, t_ray *light, t_hitinfo *hit);
void	lights_init(t_data *data, char *line, int nb_lights);
t_ray    *get_lights_rays(t_data *data, int j);

// VECTOR UTILS
t_vect 	sum_vect(t_vect pos_1, t_vect pos_2);
t_vect	sub_vect(t_vect pos_1, t_vect pos_2);
float	dot_product(t_vect pos_1, t_vect pos_2);
t_vect	cross_product(t_vect a, t_vect b);
t_vect	normalize(t_vect v_orig);
float	magnitude(t_vect v);
t_vect	create_vector(float x, float y, float z);
t_vect	scale_vect(t_vect v, float scalar);
t_vect	scale_down(t_vect v, float scalar);
// MATH UTILS
int		square(float i);
double	ft_atol(const char *nptr);
float	max_nb(float nb1, float nb2);
float	min_nb(float nb1, float nb2);
float	ratio(float nb1, float nb2);
void	swap(float *a, float *b);
// DEBUG UTILS
void 	print_all_obj(t_data *data);
void	print_object(t_objs *object, t_type_obj type);
void	print_sphere(t_sphere *sphere);
void	print_plane(t_plane *plane);
void	print_camera(t_camera camera);
void	print_ray(t_ray ray);
void	print_rgb(t_rgb color);
void	print_vect(t_vect vectr);

//COLOR CREATION
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
//COLOR
int     create_color(t_rgb rgb, t_ambient ambient);
t_rgb     create_color_rgb(t_rgb rgb, t_ambient ambient);

int     create_color_int(t_rgb rgb);
int 	just_color(t_rgb rgb);
t_rgb	extract_color(int r, int g, int b);
t_rgb	extract_color_from_int(int color);
t_vect	rgb_to_vect(t_rgb color);
int		interpolate_color(int color1, int color2, float ratio);

//	WINDOW MANAGEMENT
int		keys(int keysym, t_data *map);
int		esc_x(t_data *data);
//SPLIT
char	**ft_split_rt(char const *s, char c);
//SAFE FT
void    *safe_malloc(size_t size);
//FREE FUNCTIONS
void	free_mtx(char **mtx);
//ERRORS
void	print_error(char *message);

#endif
