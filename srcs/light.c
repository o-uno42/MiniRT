#include "../includes/minirt.h"
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

bool light_intersect(t_data *data, t_ray *light, t_ray camera_ray, int index)
{
    // First get the camera ray intersection point with the sphere
    t_vect oc_camera;
    oc_camera.x = camera_ray.pos.x - data->obj[index].sphere->pos.x;
    oc_camera.y = camera_ray.pos.y - data->obj[index].sphere->pos.y;
    oc_camera.z = camera_ray.pos.z - data->obj[index].sphere->pos.z;
    
    float a_camera = dot_product(camera_ray.dir, camera_ray.dir);
    float b_camera = 2.0f * dot_product(oc_camera, camera_ray.dir);
    float c_camera = dot_product(oc_camera, oc_camera) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);
    float discriminant_camera = b_camera * b_camera - 4 * a_camera * c_camera;
    
    if (discriminant_camera < 0)
        return false;

    // Calculate camera intersection point
    float t_camera = (-b_camera - sqrt(discriminant_camera)) / (2 * a_camera);
    t_vect hit_point;
    hit_point.x = camera_ray.pos.x + camera_ray.dir.x * t_camera;
    hit_point.y = camera_ray.pos.y + camera_ray.dir.y * t_camera;
    hit_point.z = camera_ray.pos.z + camera_ray.dir.z * t_camera;
    
    // Now check if any light ray can reach this point
    int i = 0;
    while (i < data->light.nb_rays)
    {
        // Vector from light to hit point
        t_vect to_hit;
        to_hit.x = hit_point.x - light[i].pos.x;
        to_hit.y = hit_point.y - light[i].pos.y;
        to_hit.z = hit_point.z - light[i].pos.z;
        
        // Get distance to hit point
        float dist = sqrt(dot_product(to_hit, to_hit));
        
        // Normalize to_hit vector
        to_hit.x /= dist;
        to_hit.y /= dist;
        to_hit.z /= dist;
        
        // Compare with light ray direction
        float dot = dot_product(to_hit, light[i].dir);
        
        // If the dot product is close to 1, the light ray is pointing at our hit point
        if (dot >= 0) {  // You might need to adjust this threshold
            // Check if there's no intersection with sphere before hit point
            t_vect oc;
            oc.x = light[i].pos.x - data->obj[index].sphere->pos.x;
            oc.y = light[i].pos.y - data->obj[index].sphere->pos.y;
            oc.z = light[i].pos.z - data->obj[index].sphere->pos.z;
            
            float a = dot_product(light[i].dir, light[i].dir);
            float b = 2.0f * dot_product(oc, light[i].dir);
            float c = dot_product(oc, oc) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);
            float discriminant = b * b - 4 * a * c;
            
            if (discriminant >= 0) {
                float t = (-b - sqrt(discriminant)) / (2 * a);
                if (t > 0 && t <= dist) {  // Check if intersection is before our hit point
                    return true;
                }
            }
        }
        i++;
    }
    return false;
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
        rays[i].dir.x *= data->light.bright;
        rays[i].dir.y *= data->light.bright;
        rays[i].dir.z *= data->light.bright;
        
        i++;
    }
    return (rays);
}