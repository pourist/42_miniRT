#include "materials.h"

t_material	*new_material(t_material *material)
{
	*material = (t_material){
		.color = new_color(1.0, 1.0, 1.0),
		.ambient = new_color(0.1, 0.1, 0.1),
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200.0,
		.pattern.has_pattern = false,
		.reflective = 0.0,
		.transparency = 0.0,
		.refractive_index = VACUUM,
	};
	return (material);
}
