/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:01:30 by tjuvan            #+#    #+#             */
/*   Updated: 2024/11/06 22:11:39 by tjuvan           ###   ########.fr       */
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
}

void print_all_obj(t_data *data)
{
	int i;

	i = -1;
	while (data->obj[++i].type_obj != END)
	{
		printf("object index: %d \t", i);
		print_object(&data->obj[i], data->obj[i].type_obj);
	}
}



