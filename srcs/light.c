#include "../includes/minirt.h"
#include <stdbool.h>

bool    light_intersect(t_data *data, t_ray *light)
{
	t_vect	offset_vect;
	float	intersect1;
	float	intersect2;


	offset_vect = sub_vect(data->camera.pos, data->obj[index].sphere->pos);

	float a = dot_product(camera_ray.dir, camera_ray.dir);
	float b = 2.0 * dot_product(camera_ray.dir, offset_vect);
	float c = dot_product(offset_vect, offset_vect) - square(data->obj[index].sphere->radius);
	if (solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0)
			return (true);
	}
	return (false);
}

t_ray    *light_rays(t_data *data)
{
    int nb_rays;
    int i = 0;
    t_ray *ray;

    nb_rays = 300;
    ray = safe_malloc(sizeof(t_ray) *nb_rays + 1);
    ray->pos = data->light.pos;
    while (i < nb_rays)
    {
        double theta = ((double)rand() / RAND_MAX) * 2.0 * PI;
        double phi = ((double)rand() / RAND_MAX) * PI;
        ray->dir.x = sin(phi) * cos(theta);
        ray->dir.y = sin(phi) * sin(theta);
        ray->dir.z = cos(phi);
        ray->dir = normalize(ray->dir);
        ray->dir.x *= data->light.bright;
        ray->dir.y *= data->light.bright;
        ray->dir.z *= data->light.bright;
        ray[i].dir = ray->dir;
        i++;
    }
    return (ray);
}