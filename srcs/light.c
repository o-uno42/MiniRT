#include "../includes/minirt.h"
#include <stdbool.h>

bool    light_intersect(t_data *data, t_ray *light, int index)
{
    printf("light: %f\n", light->pos.x);
    // printf("light: %f\n", light->bright);
    int i = 0;
    t_vect oc;
    while (i < data->light.nb_rays)
    {
        oc.x = light[i].pos.x - data->obj[index].sphere->pos.x, 
        oc.y = light[i].pos.y - data->obj[index].sphere->pos.y, 
        oc.z = light[i].pos.z - data->obj[index].sphere->pos.z;
        float a = dot_product(light[i].dir, light[i].dir);
        float b = 2.0f * dot_product(oc, light[i].dir);
        float c = dot_product(oc, oc) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);
        
        float discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            return true;
        } else {
            return false;
        }
        i++;
    }
    return false;
}

t_ray    *light_rays(t_data *data)
{
    int nb_rays;
    int i = 0;
    t_ray *ray;

    nb_rays = 300;
    data->light.nb_rays = nb_rays;
    ray = safe_malloc(sizeof(t_ray) *nb_rays);
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