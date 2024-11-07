#include "../includes/minirt.h"
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


t_vect get_sphere_normal(t_data *data, t_ray camera_ray, int index) {
    camera_ray = camera_ray;
    
    t_vect normal;
    
    normal = sub_vect(data->intersect->t0, data->obj[index].sphere->pos);
    return (normalize(normal));
}

t_vect   specular_light_sphere(t_data *data, t_ray *light, t_ray camera_ray, int index)
{
    t_vect reflection_vect;
    t_vect scaled;
    float dot;
    t_vect sphere_normal;

    sphere_normal = get_sphere_normal(data, camera_ray, index);


    dot = dot_product(sphere_normal, light->dir);
    scaled = scale_vector(sphere_normal, 2 * dot);
    reflection_vect = sub_vect(scaled, light->dir);

    return (reflection_vect);
}



bool light_intersect(t_data *data, t_ray *light, t_ray camera_ray, int index)
{
    t_vect oc_camera; //vettore che va dal centro della sfera al ray della camera
    float a_camera;
    float b_camera;
    float c_camera;
    float discriminant_sphere;
    float t_camera;
    
    t_vect light_dir; //vettore che va dalla light.pos ai punti visibili della sfera
    float dist_to_hit;
    t_vect block; //controlla se la sfera blocca il passaggio della luce

    oc_camera.x = camera_ray.pos.x - data->obj[index].sphere->pos.x;
    oc_camera.y = camera_ray.pos.y - data->obj[index].sphere->pos.y;
    oc_camera.z = camera_ray.pos.z - data->obj[index].sphere->pos.z;
    
    a_camera = dot_product(camera_ray.dir, camera_ray.dir);
    b_camera = 2.0f * dot_product(oc_camera, camera_ray.dir);
    c_camera = dot_product(oc_camera, oc_camera) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);
    discriminant_sphere = b_camera * b_camera - 4 * a_camera * c_camera; //per capire se interseca la sfera
    
    if (discriminant_sphere < 0)
        return (false);

    t_camera = (-b_camera - sqrt(discriminant_sphere)) / (2 * a_camera);
    // if (t_camera < 0)
    //     return false; //servirebbe a restituire false se l'intersezione è dietro la camera

    t_vect hit_point;
    hit_point.x = camera_ray.pos.x + camera_ray.dir.x * t_camera;
    hit_point.y = camera_ray.pos.y + camera_ray.dir.y * t_camera;
    hit_point.z = camera_ray.pos.z + camera_ray.dir.z * t_camera;
    
    int i = 0;
    while (i < data->light.nb_rays *  data->light.bright)
    {
        light_dir.x = hit_point.x - light[i].pos.x;
        light_dir.y = hit_point.y - light[i].pos.y;
        light_dir.z = hit_point.z - light[i].pos.z;
        
        dist_to_hit = sqrt(dot_product(light_dir, light_dir));

        light_dir = normalize(light_dir);
        
        block.x = light[i].pos.x - data->obj[index].sphere->pos.x;
        block.y = light[i].pos.y - data->obj[index].sphere->pos.y;
        block.z = light[i].pos.z - data->obj[index].sphere->pos.z;
        
        float a = dot_product(light_dir, light_dir);
        float b = 2.0f * dot_product(block, light_dir);
        float c = dot_product(block, block) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);
        float discriminant = b * b - 4 * a * c;
        
        //se la luce interseca la sfera:
        if (discriminant >= 0) {
            float t1 = (-b - sqrt(discriminant)) / (2 * a);
            float t2 = (-b + sqrt(discriminant)) / (2 * a);
            
            if ((t1 < dist_to_hit) || 
                (t2 < dist_to_hit)) {
                    
                return (true); //c'è ombra
            
            }
        }
        i++;
    }
    return (false); //è colpito dalla luce
}

t_vect reflect(t_vect in, t_vect normal) {
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

// t_ray    *reflection_rays(t_data *data)
// {
//     int nb_rays;
//     int i = 0;
//     t_ray *rays;

//     nb_rays = 300;
//     data->light.nb_rays = nb_rays;
//     rays = safe_malloc(sizeof(t_ray) * nb_rays);
    
//     while (i < nb_rays)
//     {
//         rays[i].pos = data->light.pos;

//         // rand restituisce un int random
//         double theta = ((double)rand() / RAND_MAX) * 2.0 * PI;
//         double phi = ((double)rand() / RAND_MAX) * PI;

//         rays[i].dir.x = sin(phi) * cos(theta);
//         rays[i].dir.y = sin(phi) * sin(theta);
//         rays[i].dir.z = cos(phi);
//         rays[i].dir = normalize(rays[i].dir);
//         // rays[i].dir.x *= data->light.bright;
//         // rays[i].dir.y *= data->light.bright;
//         // rays[i].dir.z *= data->light.bright;
        
//         i++;
//     }
//     return (rays);
// }
