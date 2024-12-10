#include "../../includes/minirt.h"

bool	render_sphere_shadow(t_ray camera_ray, t_data *data, t_sphere *sphere,
		t_hitinfo *hit)
{
	t_vect	offset_vect;
	float	intersect1;
	float	intersect2;

	offset_vect = sub_vect(camera_ray.pos, sphere->pos);
	data->a = dot_product(camera_ray.dir, camera_ray.dir);
	data->b = 2.0 * dot_product(camera_ray.dir, offset_vect);
	data->c = dot_product(offset_vect, offset_vect) - square((*sphere).radius);
	if (solve_quadratic(data, &intersect1, &intersect2))
	{
		if (intersect1 > 0.0003)
		{
			calc_hit_sphere(hit, intersect1, camera_ray, sphere);
			return (true);
		}
	}
	intersect1 = FLT_MAX;
	calc_hit_sphere(hit, intersect1, camera_ray, sphere);
	return (false);
}