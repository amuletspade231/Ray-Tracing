#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;

    color = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

    if(recursion_depth < world.recursion_depth_limit) {
	vec3 view = ray.endpoint - intersection_point;
	vec3 reflection = (2 * dot(view, normal) * normal - view).normalized();
	Ray reflecting_ray(intersection_point, reflection);
	color += reflectivity * world.Cast_Ray(reflecting_ray, recursion_depth + 1);
    }

    return color;
}
