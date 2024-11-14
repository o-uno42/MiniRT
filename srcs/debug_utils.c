/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:01:30 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/13 14:55:55 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_vect(t_vect vectr)
{
	printf("vect: x: [%f], y: [%f], z: [%f] \n", vectr.x, vectr.y, vectr.z);
}

void	print_rgb(t_rgb color)
{
	printf("rgb: r: %d, g: %d, b: %d\n", color.r, color.g, color.b);
}

void	print_ray(t_ray ray)
{
	printf("RAY\n");
	printf("ray.pos: ");
	print_vect(ray.pos);
	printf("ray.dir: ");
	print_vect(ray.dir);
	printf("\n");
}

void	print_camera(t_camera camera)
{
	printf("CAMERA \n");
	printf("camera.pos: ");
	print_vect(camera.pos);
	printf("camera.dir: ");
	print_vect(camera.dir);
	printf("camera.forward: ");
	print_vect(camera.forward);
	printf("camera.right: ");
	print_vect(camera.right);
	printf("camera.up: ");
	print_vect(camera.up);
	printf("camera.fov: %f\n", camera.fov);
	printf("\n");
}

void	print_sphere(t_sphere *sphere)
{
	printf("SPHERE\n");
	printf("sphere.pos: ");
	print_vect((*sphere).pos);
	printf("diameter: %f, radius: %f, color: ", (*sphere).diameter, (*sphere).radius);
	print_rgb((*sphere).rgb);
	printf("\n");
}

void	print_cylinder(t_cylinder *cylinder)
{
	printf("CYLINDER\n");
	printf("cylinder.pos: ");
	print_vect((*cylinder).pos);
	printf("cylinder.p1: ");
	print_vect((*cylinder).p1);
	printf("cylinder.p2: ");
	print_vect((*cylinder).p2);
	printf("diameter: %f, radius: %f, height: %f color: ", (*cylinder).diameter, (*cylinder).radius, (*cylinder).height);
	print_rgb((*cylinder).rgb);
	printf("\n");
}

void	print_cone(t_cone *cone)
{
	printf("CONE\n");
	printf("cone.pos: ");
	print_vect((*cone).pos);
	printf("cone.p1: ");
	print_vect((*cone).p1);
	printf("cone.p2: ");
	print_vect((*cone).p2);
	printf(" theta radians: %f, theta degrees: %f \n", (*cone).theta_r, (*cone).theta_d);
	printf("diameter: %f, radius: %f, height: %f color: ", (*cone).diameter, (*cone).radius, (*cone).height);
	print_rgb((*cone).rgb);
	printf("\n");
}

void	print_hyperboloid(t_hyperboloid *hyperboloid)
{
	printf("HYPERBOLOID\n");
	printf("hyperboloid.pos: ");
	print_vect((*hyperboloid).pos);
	printf("hyperboloid.dir: ");
	print_vect((*hyperboloid).dir);
	printf("a: %f, b: %f, c: %f color: ", (*hyperboloid).a, (*hyperboloid).b, (*hyperboloid).c);
	print_rgb((*hyperboloid).rgb);
	printf("\n");
}
void	print_plane(t_plane *plane)
{
	printf("PLANE\n");
	printf("plane.pos: ");
	print_vect((*plane).pos);
	printf("plane.vect: ");
	print_vect((*plane).vect);
	print_rgb((*plane).rgb);
	printf("\n");
}

void	print_object(t_objs *object, t_type_obj type)
{
	if (type == SPHERE)
		print_sphere(object->object);
	else if (type == PLANE)
		print_plane(object->object);
	else if (type == CYLINDER)
		print_cylinder(object->object);
	else if (type == HYPERBOLOID)
		print_hyperboloid(object->object);
	else if (type == CONE)
		print_cone(object->object);
}

void	print_pic(t_picture pic)
{
	printf("PICTURE nr:%d \n", pic.index);
	printf(" path:%s \t line_len: %d \t w:%d, h:%d \t bpp:%d \t endian:%d \n", pic.path, pic.line_len, pic.w, pic.h, pic.bpp, pic.endian);
	printf("data:%s \n\n", pic.data);
}

void	print_pictures(t_data *data)
{
	int	i;
	
	i = 0;
	while (i <= data->pic_idx)
		print_pic(data->pics[i]);
}

void print_all_obj(t_data *data)
{
	int i;

	i = -1;
	while (data->obj[++i].type_obj != END)
	{
		printf("object index: %d \t", i);
		print_object(&data->obj[i], data->obj[i].type_obj);
		/* print_pictures(data); */
	}
}



