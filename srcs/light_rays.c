#include "../includes/minirt.h"


// t_ray    *light_rays(t_data *data)
// {
//     int i = 0;
//     t_ray *rays;

//     data->light.nb_rays = NB_RAYS;
//     rays = safe_malloc(sizeof(t_ray) * NB_RAYS);
//     while (i < NB_RAYS)
//     {
//         rays[i].pos = data->light.pos;
//         double theta = ((double)rand() / RAND_MAX) * 2.0 * PI;
//         double phi = ((double)rand() / RAND_MAX) * PI;
//         rays[i].dir.x = sin(phi) * cos(theta);
//         rays[i].dir.y = sin(phi) * sin(theta);
//         rays[i].dir.z = cos(phi);
//         rays[i].dir = normalize(rays[i].dir);
//         i++;
//     }
//     return (rays);
// }

// t_ray    *light_bonus_rays(t_data *data, int j)
// {
//     int i = 0;
//     t_ray *rays;

//     data->light.nb_rays = NB_RAYS;
//     rays = safe_malloc(sizeof(t_ray) * NB_RAYS);
//     while (i < NB_RAYS)
//     {
//         rays[i].pos = data->light_bonus[j].pos;
//         double theta = ((double)rand() / RAND_MAX) * 2.0 * PI;
//         double phi = ((double)rand() / RAND_MAX) * PI;
//         rays[i].dir.x = sin(phi) * cos(theta);
//         rays[i].dir.y = sin(phi) * sin(theta);
//         rays[i].dir.z = cos(phi);
//         rays[i].dir = normalize(rays[i].dir);
//         i++;
//     }
//     return (rays);
// }