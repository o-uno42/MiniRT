#include "../includes/minirt.h"
#include <stdbool.h>

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


void	calc_hit_sphere_2(t_hitinfo hit, float intersect, t_ray ray, t_sphere *sphere)
{
	if (intersect >= hit.t)
		return ;
	hit.t = intersect;
	hit.p = sum_vect(ray.pos, scale_vect(ray.dir, intersect));
	hit.normal = normalize(sub_vect(hit.p, sphere->pos));
	hit.rgb = sphere->rgb;
	if (dot_product(ray.dir, hit.normal) < 0)
		hit.is_outside = true;
	else
	{
		hit.normal = scale_vect(hit.normal, -1);
		hit.is_outside = false;
	}
}

bool	render_sphere_shadow(t_ray shadow_ray, t_data *data, t_sphere *sphere, t_hitinfo hit)
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
bool is_behind_plane(t_light light, t_plane *plane)
{
    float D = dot_product(plane->vect, light.pos);
    float t = D - (dot_product(plane->vect, plane->pos));
    if (t < 0.000001)
        return true;
    else
        return false;
}
bool render_plane_shadow(t_light light, t_ray shadow_ray, t_plane *plane, t_hitinfo hit)
{
    bool res;

    res = true;
    float visibility = dot_product(plane->vect, shadow_ray.dir);
    if (visibility < 0.0003)
        return false;
    if (!is_behind_plane(light, plane))
        return false;
    float D = (dot_product(plane->vect, shadow_ray.pos));
    float t = D - dot_product(plane->vect, plane->pos);
    if (t < 0.0003|| t >= hit.t)
        res = true;
    return res;
}


bool	caps_2(t_ray camera_ray, t_cylinder *cylinder, t_hitinfo hit)
{
	float	visibility;
	float	visibility2;
	float	chosen_t;
	POINT	p;
	POINT	pcenter;
	t_vect	pdelt;
	t_vect	normal;

	visibility = dot_product(cylinder->dir, camera_ray.dir);
	visibility2 = dot_product(scale_vect(cylinder->dir, -1), camera_ray.dir);
	if (visibility <= 0 && visibility2 <= 0)
		return (false);

	float t = dot_product(cylinder->dir, sub_vect(cylinder->p1, camera_ray.pos)) / visibility;
	float t2 = dot_product(scale_vect(cylinder->dir, -1), sub_vect(cylinder->p2, camera_ray.pos)) / visibility2;

	if (t2 > 0 && (t <= 0 || t > t2))
	{
		chosen_t = t2;
		normal = scale_vect(cylinder->dir, -1);
		pcenter = cylinder->p2;
	}
	else if (t > 0 && (t2 <= 0 || t2 > t))
	{
		chosen_t = t;
		pcenter = cylinder->p1;
		normal = cylinder->dir;

	}
	else
		return (false);
	if (chosen_t > hit.t)
		return (false);
	p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, chosen_t));
	pdelt = sub_vect(p, pcenter);
	if (magnitude(pdelt) <= cylinder->radius && chosen_t < hit.t)
	{
		hit.normal = normal;
		// cap_hit(cylinder, hit, p, chosen_t); 
		// cap_texture(hit, cylinder);
		// cap_bump(hit, cylinder);
		return (true);
	}	

	return (false);
}


bool cyl_end_2(t_hitinfo hit, t_ray camera_ray, t_cylinder *cylinder, POINT *res)
{
	t_vect	hypotenuse;
	t_vect	proj;
	t_vect	p_to_res;
	float	proj_len;

	camera_ray = camera_ray;
	hypotenuse = sub_vect(hit.p, cylinder->pos);
	proj = scale_vect(cylinder->dir, dot_product(hypotenuse, cylinder->dir));
	*res = sum_vect(cylinder->pos, proj);
	p_to_res = sub_vect(*res, cylinder->p2);
	proj_len = dot_product(p_to_res, cylinder->dir);
	if (proj_len >= 0 && proj_len <= cylinder->height)
		return (true);
	else
		return (false);
}

bool	calc_hit_cyl_2(t_hitinfo hit, float intersect, t_ray camera_ray, t_cylinder *cylinder)
{
	float prev_hit;
	POINT	prev;
	POINT	res;
	
	prev_hit = hit.t;
	prev = hit.p;
	if (intersect >= hit.t + 0.0003)
		return false;
	hit.t = intersect;
	hit.p = sum_vect(camera_ray.pos, scale_vect(camera_ray.dir, intersect));
	if(!cyl_end_2(hit, camera_ray, cylinder, &res))
	{
		hit.t = prev_hit;
		hit.p = prev;
		return false;
	}
	hit.normal = normalize(sub_vect(hit.p, res));
	// checker_cyl(hit, cylinder);
	// tex_cyl(&hit, cylinder);
	// cyl_bump(&hit, cylinder);
    return true;
}

bool	render_cylinder_shadow(t_ray shadow_ray, t_data *data, t_cylinder *cylinder, t_hitinfo hit)
{
	float	a;
	float	b;
	float	c;
	float	intersect1;
	float	intersect2;
	t_vect	comp;
	t_vect	pdelt;
	t_vect	b1;
	t_vect	c1;

	data=data;
	pdelt = sub_vect(shadow_ray.pos, cylinder->pos);
	comp = sub_vect(shadow_ray.dir, scale_vect(cylinder->dir, dot_product(shadow_ray.dir, cylinder->dir)));
	a = dot_product(comp, comp);
	b1 = sub_vect(pdelt, scale_vect(cylinder->dir, dot_product(pdelt, cylinder->dir)));
	b = 2 * dot_product(comp, b1); 
	c1 = sub_vect(pdelt, scale_vect(cylinder->dir, dot_product(pdelt, cylinder->dir)));
	c = dot_product(c1, c1) - cylinder->radius * cylinder->radius;
	if(solve_quadratic(a, b, c, &intersect1, &intersect2))
	{
        if (intersect1 > 0.0001 && intersect1 < hit.t)
		{
			if(calc_hit_cyl_2(hit, intersect1, shadow_ray, cylinder))
			return (true);
		}
	}
    // printf("1] %f\n", intersect1);
    // printf("2] %f\n", intersect2);
    if (hit.t > intersect1 && intersect2 > intersect1)
	{if (caps_2(shadow_ray, cylinder, hit))
		return (true);}
	return (false);
}

int intersect_object(t_data *data, t_objs object, t_ray ray, t_hitinfo hit, int i) 
{
    data = data;

    if (object.type_obj == SPHERE)
        return (render_sphere_shadow(ray, data, object.object, hit));
    else if (object.type_obj == PLANE)
        return (render_plane_shadow(data->lights[i], ray, object.object, hit));
        // return (intersect_plane(object.object, ray, hit));
    else if (object.type_obj == CYLINDER)
        return (render_cylinder_shadow(ray, NULL, object.object, hit));
    return (0);
}


t_vect	reflect_vect(t_vect v, t_vect n)
{
	t_vect	dst;

	dst = scale_vect(n, 2 * dot_product(v, n));
	dst = sub_vect(dst, v);
	return (dst);
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

float luminance(t_rgb color) {
    return 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
}

bool tonality_is_relevant(t_rgb color1)
{
    if ((color1.r == color1.g) && (color1.r == color1.b))
        return false;
    else if (color1.r > 240 && color1.g > 240 && color1.b)
        return false;
    else
        return true;
}

t_rgb mix_rgb(t_rgb color1, t_rgb color2) {
    float luminance1;
    float luminance2;
    t_rgb mixed_color;
    float mixed_luminance;
    float adjustment;
    double scale;

    luminance1 = luminance(color1);
    luminance2 = luminance(color2);
    mixed_color.r = (color1.r + color2.r) / 2;
    mixed_color.g = (color1.g + color2.g) / 2;
    mixed_color.b = (color1.b + color2.b) / 2;
    mixed_luminance = luminance(mixed_color);
    adjustment = (luminance1 + luminance2) / 2;
    scale = adjustment / mixed_luminance;
    mixed_color.r = min_nb((int)(mixed_color.r * scale), 255);
    mixed_color.g = min_nb((int)(mixed_color.g * scale), 255);
    mixed_color.b = min_nb((int)(mixed_color.b * scale), 255);
    return mixed_color;
}

t_rgb  calculate_specular(t_data *data, t_hitinfo *hit, t_vect light_dir, t_ray camera_ray, float shininess)
{
    data = data;
    // t_rgb white;
    t_vect reflect;
    t_vect view_dir;

    // white.r = 0;
    // white.g = 0;
    // white.b = 0;
    reflect = reflect_vect(hit->normal, light_dir);
    reflect = normalize(reflect);
    view_dir = sub_vect(camera_ray.pos, hit->p);
    view_dir = normalize(view_dir);
    float spec = max_nb(0, dot_product(reflect, view_dir));
    spec = pow(spec, shininess);
    return bright_rgb(hit->rgb, spec);
}

float get_total_intensity(t_light light, t_hitinfo *hit, t_vect light_dir, float dist_to_light)
{
    float angle_intensity;
    float distance_factor;

    angle_intensity = max_nb(0.0f, dot_product(hit->normal, light_dir));
    distance_factor = 1 / (1 + 0.1 * square(dist_to_light));
    return (angle_intensity * distance_factor * light.bright);
}

t_rgb clamp_rgb(t_rgb color)
{
    if (color.r < 0)
        color.r = 0;
    else if (color.r > 255)
        color.r = 255;
    if (color.g < 0)
        color.g = 0;
    else if (color.g > 255)
        color.g = 255;
    if (color.b < 0)
        color.b = 0;
    else if (color.b > 255)
        color.b = 255;
    return color;
}


bool check_shadow(t_data *data, t_vect point, t_hitinfo hit)
{
    bool    in_shadow;
    t_ray shadow_ray;
    t_hitinfo shadow_hit;
    int     j;
    int     i;

    j = 0;
    i = 0;

	shadow_hit.t = INFINITY;
    while (j < data->nb_lights)
    {
        shadow_ray.pos = sum_vect(point, scale_vect(hit.normal, 0.0003)); // why is here shadow ray pos not hit.p?
        shadow_ray.dir = normalize(sub_vect(data->lights[j].pos, point));
        in_shadow = false;
        i = 0;
        while (data->obj[i].type_obj != END)
        {
            if (intersect_object(data, data->obj[i], shadow_ray, shadow_hit, j))
            {
                    in_shadow = true;
                    break;
            }
            i++;
        }
        if (!in_shadow)
            break;
        j++;
    }
    return in_shadow;
}

t_rgb lights_intersect(t_data *data, t_ray camera_ray, t_hitinfo *hit, int x, int y)
{
    x =x ;
    y = y;
    t_rgb final_color = {0,0,0};
    float total_intensity = 0;
    t_rgb diffuse = {0,0,0};
    t_rgb specular = {0,0,0};


    int i = 0;
    while (i < data->nb_lights)
    {
        // t_light light = data->lights[i];
        t_vect light_dir = sub_vect(data->lights[i].pos, hit->p);
        float dist_to_light = magnitude(light_dir); //sqrt(dot_product(light_dir, light_dir));
        light_dir = normalize(light_dir);
    
        if (check_shadow(data, hit->p, *hit))
        {
            float angle_intensity = max_nb(0.0f, dot_product(hit->normal, light_dir));
            float distance_factor = 1 / (1 + 0.1 * square(dist_to_light));
            float shadow_intensity = (1.0 + angle_intensity) * distance_factor * data->lights[i].bright;
            float shadow_strength = 1.0f; 
            float shadow_distance_factor = (50 * dist_to_light);
            float darkness = shadow_intensity * (1.0f + shadow_distance_factor) * shadow_strength * 5;

            t_rgb color_with_ambient = create_color_rgb(hit->rgb, data->ambient);
            final_color = dark_rgb(color_with_ambient, darkness);
        }
        else
        {
            total_intensity = get_total_intensity(data->lights[i], hit, light_dir, dist_to_light);
            if (tonality_is_relevant(data->lights[i].rgb))
                diffuse = bright_rgb(mix_rgb(hit->rgb, data->lights[i].rgb), total_intensity * 5000 * 0.5);
            else
                diffuse = bright_rgb(hit->rgb, total_intensity * 5000 * 0.5);
            specular = calculate_specular(data, hit, light_dir, camera_ray, 10);
            t_rgb sum_color = add_rgb(diffuse, specular);
            final_color = add_rgb(sum_color, final_color);
        }
        i++;
    }
    return clamp_rgb(final_color);
}


// t_rgb light_intersect(t_data *data, t_ray *light, t_ray camera_ray, t_hitinfo *hit, int x, int y)
// {
//     light = light;
//     camera_ray = camera_ray;
//     int i;
//     int j;
//     float total_intensity;
//     t_vect light_dir;
//     float dist_to_light;
//     bool in_shadow;
//     t_hitinfo shadow_hit;
//     t_ray shadow_ray;

//     float angle_intensity;
//     float distance_factor;
//     // float light_intensity;

//     i = 0;
//     j = 0;
//     total_intensity = 0;
//     in_shadow = false;
//     while (data->obj[i].type_obj != END) 
//     {
//         // t_light light = data->lights[i];
//         light_dir = sub_vect(light->pos, hit->p);
//         dist_to_light = sqrt(dot_product(light_dir, light_dir));
//         light_dir = normalize(light_dir);
        
//         shadow_ray.pos = hit->p; 
//         shadow_ray.dir = light_dir;
//         in_shadow = false;
//         j = 0;
//         while (data->obj[j].type_obj != END)
//         {
//             if (intersect_object(data, data->obj[j], &shadow_ray, &shadow_hit)  && shadow_hit.t < dist_to_light) 
//             {
//                 if (shadow_hit.t > 0.0001) {
//                     in_shadow = true;
//                     break;
//                 }
//             }
//             j++;
//         }
//         angle_intensity = max_nb(0.0f, dot_product(hit->normal, light_dir));
//         distance_factor = 1 / (1 + 0.1 * square(dist_to_light));
//         // total_intensity = 0.001;
//         // total_intensity = get_total_intensity(light, hit, light_dir, dist_to_light);
//         if (!in_shadow) {
//             if (total_intensity > 0) {
//                 if (create_color_int(bright_rgb(add_rgb(hit->rgb, data->light.rgb), total_intensity * 1000)) > create_color_int(add_rgb(hit->rgb, data->light.rgb)))
//                 {
//                     t_rgb diffuse = bright_rgb(add_rgb(hit->rgb, data->light.rgb), total_intensity * 1000);
//                     t_rgb specular = calculate_specular(data, hit, light_dir, camera_ray, 10);
//                     hit->rgb = add_rgb(diffuse, specular);
//                     my_pixel_put(data, x, y, just_color(hit->rgb));
//                 }
//                 return (hit->rgb);
//             }
//         }
//         float shadow_intensity = (1.0 - angle_intensity) * distance_factor * data->light.bright;
//         float shadow_strength = 1.0f; 
//         float shadow_distance_factor = (1.0f + 0.1 * dist_to_light);
//         float darkness = shadow_intensity * (1.0f + shadow_distance_factor) * shadow_strength * 30;
//         if (darkness > 0)
//         {
//             if (just_color(dark_rgb(hit->rgb, darkness)) > just_color(hit->rgb))
//                 hit->rgb = hit->rgb;
//             else 
//                 hit->rgb = dark_rgb(hit->rgb, darkness);
//         }
//         i++;
//     }
//     my_pixel_put(data, x, y, just_color(hit->rgb));
//     return (hit->rgb);
// }


// t_ray    *light_rays(t_data *data)
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
        
//         i++;
//     }
//     return (rays);
// }

t_ray    *get_lights_rays(t_data *data, int j)
{
    int nb_rays;
    int i = 0;
    t_ray *rays;

    nb_rays = 10;
    data->light.nb_rays = nb_rays;
    rays = safe_malloc(sizeof(t_ray) * nb_rays);

        // rays = light_rays(data);
    while (i < nb_rays)
    {
        rays[i].pos = data->lights[j].pos;

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

// t_ray    *reflection_rays(t_data *data, t_hitinfo *hit)
// {
//     int nb_rays;
//     int i = 0;
//     t_ray *rays;

//     nb_rays = 3;
//     data->light.nb_rays = nb_rays;
//     rays = safe_malloc(sizeof(t_ray) * nb_rays);
    
//     while (i < nb_rays)
//     {
//         rays[i].pos = hit->p;

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
