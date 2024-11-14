#include "../includes/minirt.h"

#include "../includes/minirt.h"
// #include <iterator>
#include <math.h>
#include <stdbool.h>

// bool    light_intersect(t_data *data, t_ray *light, t_ray camera_ray, int index)
// {
//     printf("light: %f\n", light->pos.x);
//     camera_ray = camera_ray;
//     // printf("light: %f\n", light->bright);
//     int i = 0;
//     t_vect oc;
//     while (i < data->light.nb_rays)
//     {
//         oc.x = light[i].pos.x - data->obj[index].sphere->pos.x, 
//         oc.y = light[i].pos.y - data->obj[index].sphere->pos.y, 
//         oc.z = light[i].pos.z - data->obj[index].sphere->pos.z;
//         float a = dot_product(light[i].dir, light[i].dir);
//         float b = 2.0f * dot_product(oc, light[i].dir);
//         float c = dot_product(oc, oc) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);

//         float discriminant = b * b - 4 * a * c;
//         // printf ("discr: %f\n", discriminant);

//         if (discriminant >= 0) {
//             // printf("true\n");
//             return true;
//         }
//         i++;
//     }
//     return false;
// }

//ho passato la funzione sopra a claudeAi e questo è il risultato:

int     create_color2(t_rgb rgb, t_ambient ambient, float dist)
{
    int r;
    int g;
    int b;

    r = (rgb.r + ambient.rgb.r) * ambient.ratio * dist;
    g = (rgb.g + ambient.rgb.g) * ambient.ratio * dist;
    b = (rgb.b + ambient.rgb.b) * ambient.ratio * dist;
    return ((r << 16) | (g << 8) | b);
}


// t_vect get_sphere_normal(t_data *data, t_ray camera_ray, int index) {
//     camera_ray = camera_ray;
    
//     t_vect normal;
    
//     normal = sub_vect(data->hit->t0, data->obj[index].sphere->pos);
//     return (normalize(normal));
// }

// t_vect   specular_light_sphere(t_data *data, t_ray *light, t_ray camera_ray, int index)
// {
//     t_vect reflection_vect;
//     t_vect scaled;
//     float dot;
//     t_vect sphere_normal;

//     sphere_normal = get_sphere_normal(data, camera_ray, index);


//     dot = dot_product(sphere_normal, light->dir);
//     scaled = scale_vector(sphere_normal, 2 * dot);
//     reflection_vect = sub_vect(scaled, light->dir);

//     return (reflection_vect);
// }


// static t_vect random_vect(float min, float max)
// {
//     t_vect res;

//     res.x 
//     return ();
// }


t_rgb bright_rgb(t_rgb rgb, float bright)
{
    t_rgb light_rgb;

    light_rgb.r = (int)(rgb.r + bright);
    light_rgb.g = (int)(rgb.g + bright);
    light_rgb.b = (int)(rgb.b + bright);

    if (light_rgb.r > 255) light_rgb.r = 255;
    if (light_rgb.g > 255) light_rgb.g = 255;
    if (light_rgb.b > 255) light_rgb.b = 255;

    return light_rgb;
}

t_rgb dark_rgb(t_rgb rgb, float darkness)
{
    t_rgb light_rgb;

    light_rgb.r = (int)(rgb.r - darkness);
    light_rgb.g = (int)(rgb.g - darkness);
    light_rgb.b = (int)(rgb.b - darkness);

    if (light_rgb.r < 0) light_rgb.r = 0;
    if (light_rgb.g < 0) light_rgb.g = 0;
    if (light_rgb.b < 0) light_rgb.b = 0;

    return light_rgb;
}


bool intersect_sphere(t_sphere *sphere, t_ray *ray, t_hitinfo *hit) 
{
    float x0;
    float x1;
    t_vect oc = sub_vect(ray->pos, sphere->pos);
    
    ray->dir = normalize(ray->dir);
    float a = dot_product(ray->dir, ray->dir);
    float b = 2.0f * dot_product(oc, ray->dir);
    float c = dot_product(oc, oc) - sphere->radius * sphere->radius;
    
    if(solve_quadratic(a, b, c, &x0, &x1))
    {
        if (x0 > 0 && x0 < hit->t)
        {
            hit->t = x0;

            hit->p = sum_vect(ray->pos, scale_vect(ray->dir, x0));

            hit->normal = sub_vect(hit->p, sphere->pos);
            return true;
        }
    }

    // float discriminant = b * b - 4 * a * c;
    
    // if (discriminant < 0)
    //     return false;

    // x0 = (-b - sqrt(discriminant)) / (2 * a);
    // x1 = (-b + sqrt(discriminant)) / (2 * a);
    
    // float t = x0;
    // if (t < 0)
    //     t = x1;
    // if (t < 0)
    //     return false;

    // hit->t = t;

    // hit->p = sum_vect(ray->pos, scale_vect(ray->dir, t));

    // hit->normal = sub_vect(hit->p, sphere->pos);
    // hit->normal = normalize(hit->normal);

    // print_vect(hit->normal);
    // printf("Sphere pos: (%f, %f, %f)\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
    // printf("Hit point: (%f, %f, %f)\n", hit->p.x, hit->p.y, hit->p.z);
    
    // printf ("Intersect sphere\n");
    return true;
}



void	calc_hit_sphere_2(t_hitinfo *hit, float intersect, t_ray ray, t_sphere *sphere)
{
	if (intersect >= hit->t)
		return ;
	hit->t = intersect;
	hit->p = sum_vect(ray.pos, scale_vect(ray.dir, intersect));
	hit->normal = normalize(sub_vect(hit->p, sphere->pos));
	hit->rgb = sphere->rgb;
	/* printf("hit in sphere is: %f\n", hit->t); */
	if (dot_product(ray.dir, hit->normal) < 0)
		hit->is_outside = true;
	else
	{
		hit->normal = scale_vect(hit->normal, -1);
		hit->is_outside = false;
	}
}

bool	render_sphere_shadow(t_ray shadow_ray, t_data *data, t_sphere *sphere, t_hitinfo *hit)
{
	data = data;
	t_vect	offset_vect;
	float	intersect1;
	float	intersect2;

	offset_vect = sub_vect(shadow_ray.pos, sphere->pos);

	float a = dot_product(shadow_ray.dir, shadow_ray.dir);
	float b = 2.0 * dot_product(shadow_ray.dir, offset_vect);
	float c = dot_product(offset_vect, offset_vect) - square((*sphere).radius);
	if (solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
		if (intersect1 > 0)
		{
			calc_hit_sphere_2(hit, intersect1, shadow_ray, sphere);
			return (true);
		}
	}
	intersect1 = FLT_MAX;
	calc_hit_sphere_2(hit, intersect1, shadow_ray, sphere);
	return (false);
}

bool intersect_plane(t_plane *plane, t_ray *ray, t_hitinfo *hit) 
{
    float t;
    float denom;
    t_vect dist_ray;

    plane->vect = normalize(plane->vect);
    denom = dot_product(plane->vect, ray->dir);
    dist_ray = sub_vect(plane->pos, ray->pos);
    t = dot_product(dist_ray, plane->vect) / denom;
    if (t < 0)
        return false;
    hit->t = t;
    hit->p = sum_vect(ray->pos, scale_vect(ray->dir, t));
    hit->normal = plane->vect;
    if (denom > 0)
        hit->normal = scale_vect(hit->normal, -1);
    return true;
}

int intersect_object(t_objs object, t_ray *ray, t_hitinfo *hit) 
{

    if (object.type_obj == SPHERE)
        // return (intersect_sphere(object.object, ray, hit));
        return (render_sphere_shadow(*ray, NULL, object.object, hit));
    else if (object.type_obj == PLANE)
        return (intersect_plane(object.object, ray, hit));
    else if (object.type_obj == CYLINDER)
        return (render_cylinder(*ray, NULL, object.object, hit));
    return (0);
}


t_vect	reflect_vect(t_vect v, t_vect n)
{
	t_vect	dst;

	dst = scale_vect(n, 2 * dot_product(v, n));
	dst = sub_vect(dst, v);
	return (dst);
}

int  calculate_specular(t_hitinfo *hit, t_vect light_dir, t_vect view_dir, float shininess)
{
    // t_rgb white;
    t_vect reflect;

    // white.r = 255;
    // white.g = 255;
    // white.b = 255;
    reflect = reflect_vect(hit->normal, light_dir);
    reflect = normalize(reflect);
    view_dir =  sub_vect(view_dir, hit->p);
    view_dir = normalize(view_dir);
    float spec = max_nb(0.0f, dot_product(reflect, view_dir));
    spec = pow(spec, shininess);
    return (spec);
    // if (spec > 0.001)
    //     return bright_rgb(white, spec);
    // else
    //     return (hit->rgb);
}

t_rgb add_rgb(t_rgb color1, t_rgb color2)
{
    t_rgb result;
    
    result.r = min_nb(color1.r + color2.r, 255);
    result.g = min_nb(color1.g + color2.g, 255);
    result.b = min_nb(color1.b + color2.b, 255);
    
    // print_rgb(result);
    return result;
}

bool light_intersect(t_data *data, t_ray *light, t_ray camera_ray, t_hitinfo *hit)
{
    camera_ray = camera_ray;
    int i;
    int j;
    float total_intensity;
    t_vect light_dir;
    float dist_to_light;
    bool in_shadow;
    t_hitinfo shadow_hit;
    t_ray shadow_ray;

    float angle_intensity;
    float distance_factor;
    float light_intensity;

    i = 0;
    j = 0;
    total_intensity = 0;
    in_shadow = false;
    while (data->obj[i].type_obj != END) 
    {
        light_dir = sub_vect(light[i].pos, hit->p);
        dist_to_light = sqrt(dot_product(light_dir, light_dir));
        light_dir = normalize(light_dir);
        
        shadow_ray.pos = hit->p;//sum_vect(hit->p, scale_vect(hit->normal, 0.0001)); 
        shadow_ray.dir = light_dir;
        // shadow_ray.dir = normalize(shadow_ray.dir);
        // shadow_ray.pos = scale_vect(shadow_ray.pos, -1);
        in_shadow = false;
        j = 0;
        while (data->obj[j].type_obj != END)
        {
            if (intersect_object(data->obj[j], &shadow_ray, &shadow_hit)  && shadow_hit.t < dist_to_light) 
            {
                if (shadow_hit.t > 0.0001) {
                    in_shadow = true;
                    break;
                }
            }
            j++; 
        }
    
        angle_intensity = max_nb(0.0f, dot_product(hit->normal, light_dir));
        distance_factor = 1 / (1 + 0.1 * square(dist_to_light));
        
        light_intensity = angle_intensity * distance_factor * data->light.bright;
        total_intensity += light_intensity;

    
        if (!in_shadow) {
            if (total_intensity > 0) {
                if (create_color_int(bright_rgb(hit->rgb, total_intensity * 500)) > create_color_int(hit->rgb))
                {
                    t_rgb diffuse = bright_rgb(hit->rgb, total_intensity * 500);
                    // print_rgb(diffuse);
                    // print_rgb(specular);
                    float specular = calculate_specular(hit, light_dir, camera_ray.dir, 30);
                    hit->rgb = bright_rgb(diffuse, specular);
                    // hit->rgb = diffuse;
                }
                return true;
            }
        }
        float shadow_intensity = (1.0 - angle_intensity) * distance_factor * data->light.bright;
        float shadow_strength = 1.0f; 
        float shadow_distance_factor = (1.0f + 0.05f * square(dist_to_light));
        float darkness = shadow_intensity * (1.0f + shadow_distance_factor) * shadow_strength * 20;
        hit->rgb = dark_rgb(hit->rgb, darkness);
        i++;
    }
    return false;
}


t_vect reflect(t_vect in, t_vect normal) 
{
    float dot = dot_product(in, normal);
    t_vect result;
    result.x = in.x - 2.0f * dot * normal.x;
    result.y = in.y - 2.0f * dot * normal.y;
    result.z = in.z - 2.0f * dot * normal.z;
    return result;
}

t_ray    *light_rays(t_data *data)
{
    int nb_rays;
    int i = 0;
    t_ray *rays;

    nb_rays = 300;
    data->light.nb_rays = nb_rays;
    rays = safe_malloc(sizeof(t_ray) * nb_rays);
    
    while (i < nb_rays)
    {
        rays[i].pos = data->light.pos;

        // rand restituisce un int random
        double theta = ((double)rand() / RAND_MAX) * 2.0 * PI;
        double phi = ((double)rand() / RAND_MAX) * PI;

        rays[i].dir.x = sin(phi) * cos(theta);
        rays[i].dir.y = sin(phi) * sin(theta);
        rays[i].dir.z = cos(phi);
        rays[i].dir = normalize(rays[i].dir);
        
        i++;
    }
    return (rays);
}

t_ray    *reflection_rays(t_data *data, t_hitinfo *hit)
{
    int nb_rays;
    int i = 0;
    t_ray *rays;

    nb_rays = 3;
    data->light.nb_rays = nb_rays;
    rays = safe_malloc(sizeof(t_ray) * nb_rays);
    
    while (i < nb_rays)
    {
        rays[i].pos = hit->p;

        // rand restituisce un int random
        double theta = ((double)rand() / RAND_MAX) * 2.0 * PI;
        double phi = ((double)rand() / RAND_MAX) * PI;

        rays[i].dir.x = sin(phi) * cos(theta);
        rays[i].dir.y = sin(phi) * sin(theta);
        rays[i].dir.z = cos(phi);
        rays[i].dir = normalize(rays[i].dir);
        // rays[i].dir.x *= data->light.bright;
        // rays[i].dir.y *= data->light.bright;
        // rays[i].dir.z *= data->light.bright;
        
        i++;
    }
    return (rays);
}
