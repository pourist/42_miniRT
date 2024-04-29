#include "materials.h"
#include "shapes.h"
#include <stdio.h>

t_material	new_material(void)
{
	return ((t_material){
		.color = new_color(1.0, 1.0, 1.0),
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200.0});
}

t_color	lighting(t_material const *material, t_light const *light,
				t_point const *point, t_eye_normal const *view)
{
	t_lighting_params	lp;

	lp.effective_color = hadamard_product(material->color, light->intensity);
	lp.light_v = normalize(subtract(light->position, *point));
	lp.ambient = multiply_color(lp.effective_color, material->ambient);
	lp.light_dot_normal = dot(lp.light_v, view->normal_v);
	if (lp.light_dot_normal < 0)
	{
		lp.diffuse = new_color(0, 0, 0);
		lp.specular = new_color(0, 0, 0);
	}
	else
	{
		lp.diffuse = multiply_color(lp.effective_color,
				material->diffuse * lp.light_dot_normal);
		lp.reflect_v = reflect(negate(lp.light_v), view->normal_v);
		lp.reflect_dot_eye = dot(lp.reflect_v, view->eye_v);
		if (lp.reflect_dot_eye <= 0)
			lp.specular = new_color(0, 0, 0);
		else
			lp.specular = multiply_color(light->intensity, material->specular
					* pow(lp.reflect_dot_eye, material->shininess));
	}
	return (add_color(lp.ambient, add_color(lp.diffuse, lp.specular)));
}
