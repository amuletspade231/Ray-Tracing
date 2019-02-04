#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 ambient = world.ambient_color * world.ambient_intensity * color_ambient;
    vec3 diffuse = {0,0,0};
    vec3 specular = {0,0,0};
    for (Light* light : world.lights) {
	vec3 light_vec = light->position - intersection_point;
	Ray shadow_ray(intersection_point, light_vec.normalized());
//	Hit shadow_hit = world.Closest_Intersection(shadow_ray);

//	if (shadow_hit.object == NULL || shadow_hit.dist > light_vec.magnitude()) {
	    diffuse += color_diffuse * light->Emitted_Light(-light_vec) * std::max(dot(normal.normalized(), shadow_ray.direction), 0.0);
	    
	    vec3 reflection = (light_vec - 2 * dot(light_vec, normal.normalized()) * normal).normalized();
	    specular += color_specular * light->Emitted_Light(-light_vec) * pow(std::max(dot(ray.direction, reflection) ,0.0), specular_power); 
//	}
    }
    color = ambient + diffuse + specular;
    return color;
}
