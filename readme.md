# MiniRT

A 42 project focused on **ray tracing, computer graphics and mathematical geometry** in C.

The program renders a 3D scene by tracing rays from the camera and calculating their intersections with geometric objects.

## Usage

```bash
make
./miniRT <scene.rt>
```

Example:

```bash
./miniRT scenes/example.rt
```

## Features

* Ray tracing
* Spheres, planes, cylinders and cones
* Camera and multiple light sources
* Diffuse and specular lighting
* Reflections and shadows
* Textures and checker patterns
* Bump mapping
* Vector and color operations
* Scene parsing and validation
* Real-time camera movement
* Rendering through **MiniLibX**

## Rendering

For each pixel, a camera ray is generated and tested against the objects in the scene.

The closest intersection is used to calculate the final color based on:

* Surface normals
* Light direction
* Ambient lighting
* Shadows
* Reflections
* Specular highlights
* Object textures

The project relies heavily on vector mathematics, ray-object intersection equations and color calculations.

## Main Structures

* `t_data` — global scene and rendering data
* `t_ray` — origin and direction of a ray
* `t_vect` — 3D vector operations
* `t_hitinfo` — information about a ray-object intersection
* `t_sphere` — sphere data
* `t_plane` — plane data
* `t_cylinder` — cylinder data
* `t_cone` — cone data

## Goal

The project explores how a 3D scene can be generated from mathematical descriptions of objects, cameras and light sources, turning geometry and ray calculations into a rendered image.
