#include "../includes/minirt.h"

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

    light_rgb.r = (int)(rgb.r * bright);
    light_rgb.g = (int)(rgb.g * bright);
    light_rgb.b = (int)(rgb.b * bright);

    if (light_rgb.r > 255) light_rgb.r = 255;
    if (light_rgb.g > 255) light_rgb.g = 255;
    if (light_rgb.b > 255) light_rgb.b = 255;

    return light_rgb;
}

t_rgb dark_rgb(t_rgb rgb, float darkness)
{
    t_rgb light_rgb;

    light_rgb.r = (int)(rgb.r / darkness);
    light_rgb.g = (int)(rgb.g / darkness);
    light_rgb.b = (int)(rgb.b / darkness);

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
        return (render_sphere(*ray, NULL, object.object, hit));
        // return (intersect_sphere(object.object, ray, hit));
    else if (object.type_obj == PLANE)
        return (intersect_plane(object.object, ray, hit));
    return (0);
}

bool light_intersect(t_data *data, t_ray *light, t_hitinfo *hit)
{
    int i;
    // int j;
    float total_intensity;
    t_vect light_dir;
    float dist_to_light;
    // t_ray shadow_ray;
    bool in_shadow;
    // t_hitinfo shadow_hit;

    float angle_intensity;
    float distance_factor;
    float light_intensity;
    
    i = 0;
    // j = 0;
    total_intensity = 0;
    in_shadow = false;
    while (data->obj[i].type_obj != END) 
    {
        light_dir = sub_vect(light[i].pos, hit->p);
        dist_to_light = sqrt(dot_product(light_dir, light_dir));
        light_dir = normalize(light_dir);
        // shadow_ray.pos = hit->p;
        // shadow_ray.dir = light_dir;
        // while (data->obj[j].type_obj != END) 
        // {
        //     if (intersect_object(data->obj[j], &shadow_ray, &shadow_hit)) 
        //     {
        //         if (shadow_hit.t > 0.001) {
        //             in_shadow = true;
        //             // hit->rgb = dark_rgb(hit->rgb,   100);
        //             // break;
        //         }
        //     }
        //     j++;
        // }
        if (!in_shadow) {
            // printf("Light pos: (%f, %f, %f)\n", data->light.pos.x, data->light.pos.y, data->light.pos.z);
            // printf("Light dir: (%f, %f, %f)\n", light_dir.x, light_dir.y, light_dir.z);
            // printf("Normal: (%f, %f, %f)\n", hit->normal.x, hit->normal.y, hit->normal.z);
            // printf("Angle intensity: %f\n", dot_product(hit->normal, light_dir));
            angle_intensity = max_nb(0.0f, dot_product(hit->normal, light_dir));
            distance_factor = 1 / (1 + 0.1 * square(dist_to_light));
            
            light_intensity = angle_intensity * distance_factor * data->light.bright;
            total_intensity += light_intensity;
        }
        i++;
    }
    if (total_intensity > 0) {
        // hit->rgb.r = 255;
        // hit->rgb.g = 255;
        // hit->rgb.b = 255;
        hit->rgb = bright_rgb(hit->rgb, total_intensity * 100);
        return true;
    }
    return false;
}



// bool light_intersect_later(t_data *data, t_ray *light, int i, t_ray camera_ray)//int index)
// {
//     // t_vect oc_camera; //vettore che va dal centro della sfera al ray della camera
//     // float a_camera;
//     // float b_camera;
//     // float c_camera;
//     // float discriminant_sphere;

//     // float t_camera;
//     camera_ray = camera_ray;
    
//     t_vect light_dir; //vettore che va dalla light.pos ai punti visibili della sfera
//     float dist_to_hit;
//     t_vect block; //controlla se la sfera blocca il passaggio della luce

//     t_type_obj type;
//     t_plane *plane;
//     t_sphere *sphere;
//     t_cylinder *cylinder;

//     plane = NULL;
//     sphere = NULL;
//     cylinder = NULL;
//     type = data->obj[i].type_obj;

//     if (type == SPHERE)
//         sphere = data->obj[i].object;
//     else
//         return false;;
//     // else if (type == PLANE)
//     // {
//     //     plane = data->obj[i].object;
//     //     return  false;
//     // }
//     // else if (type == CYLINDER)
//     // {
//     //     cylinder = data->obj[i].object;
//     //     return  false;
//     // }

//     // t_plane *plane = data->obj[i].ob

//     // oc_camera.x = camera_ray.pos.x - data->obj[index].sphere->pos.x;
//     // oc_camera.y = camera_ray.pos.y - data->obj[index].sphere->pos.y;
//     // oc_camera.z = camera_ray.pos.z - data->obj[index].sphere->pos.z;
    
//     // a_camera = dot_product(camera_ray.dir, camera_ray.dir);
//     // b_camera = 2.0f * dot_product(oc_camera, camera_ray.dir);
//     // c_camera = dot_product(oc_camera, oc_camera) - (data->obj[index].sphere->radius * data->obj[index].sphere->radius);
//     // discriminant_sphere = b_camera * b_camera - 4 * a_camera * c_camera; //per capire se interseca la sfera
    
//     // if (discriminant_sphere < 0)
//     //     return (false);

//     // t_camera = (-b_camera - sqrt(discriminant_sphere)) / (2 * a_camera);
//     // // if (t_camera < 0)
//     // //     return false; //servirebbe a restituire false se l'intersezione è dietro la camera

//     // t_vect hit_point;
//     // hit_point.x = camera_ray.pos.x + camera_ray.dir.x * t_camera;
//     // hit_point.y = camera_ray.pos.y + camera_ray.dir.y * t_camera;
//     // hit_point.z = camera_ray.pos.z + camera_ray.dir.z * t_camera;
    
//     // int i = 0;
//     int j = 0;
//     while (j < data->light.nb_rays *  data->light.bright)
//     {
//         // light_dir = sub_vect(hit->normal, light[i].pos);
//         // light_dir.x = hit->normal.x - light[i].pos.x;
//         // light_dir.y = hit->normal.y - light[i].pos.y;
//         // light_dir.z = hit->normal.z - light[i].pos.z;
        
//         dist_to_hit = sqrt(dot_product(light_dir, light_dir));

//         light_dir = normalize(light_dir);
    
//         if (type == SPHERE)
//            block = sub_vect(light[i].pos, sphere->pos);
//         else if (type == PLANE)
//            block = sub_vect(light[i].pos, plane->pos);
//         else if (type == SPHERE)
//            block = sub_vect(light[i].pos, cylinder->pos);
        
//         float a = dot_product(light_dir, light_dir);
//         float b = 2.0f * dot_product(block, light_dir);
//         float c = 0;
//         if (type == SPHERE)
//             c = dot_product(block, block) - square(sphere->radius);
//         // else if (type == PLANE)
//         //     c = 1;//dot_product(block, block) - square(sphere->radius);
//         // else if (type == CYLINDER)
//         //     c = 1;//dot_product(block, block) - square(sphere->radius);
//         float discriminant = b * b - 4 * a * c;
        
//         //se la luce interseca la sfera:
//         if (discriminant >= 0) {
//             float t1 = (-b - sqrt(discriminant)) / (2 * a);
//             float t2 = (-b + sqrt(discriminant)) / (2 * a);
            
//             if ((t1 < dist_to_hit) || 
//                 (t2 < dist_to_hit)) {
                    
//                 return (true); //c'è ombra
            
//             }
//         }
//         j++;
//     }
//     return (false); //è colpito dalla luce
// }

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
