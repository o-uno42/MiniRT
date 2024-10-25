#include "../includes/minirt.h"
#include <math.h>

float	scale(float point, float max_dimention)
{
	if (point < max_dimention / 2)
		return (point + (max_dimention / 2));
	else if (point > max_dimention /2)
		return (point - (max_dimention / 2));
	// if (point < 0)
	// 	return -1;
	// else if (point > max_dimention)
	// 	return -1;
	else
	 	return (point);;
	// return (unscaled_num + (old_max / 2));
}

// void   ray_points(int x, int y, t_data *data)
// {
    
// }

t_ray    camera_rays(int x, int y, t_data *data)
{
	t_ray ray;
	// t_vect coords;

	ray.dir.x = (2 * ((x + 0.5) / data->img.width) - 1) * tan(data->camera.fov / 2 * M_PI / 180) * data->img_ratio; //Later we need to check
	ray.dir.y = (1 - 2 * ((y + 0.5) / data->img.height)) * tan(data->camera.fov / 2 * M_PI / 180);
	ray.dir.z  = -1;//data->camera.dir.z;

	ray.pos.x = 0;//x - data->camera.pos.x;
	ray.pos.y = 0;//y - data->camera.pos.y;
	ray.pos.z = 0;//data->camera.pos.z;
   return (ray);
}