#include "patterns.h"
#include "shapes.h"

t_pattern	*new_pattern(t_pattern *pattern)
{
	if (!pattern)
		return (NULL);
	pattern->a = NULL;
	pattern->b = NULL;
	pattern->has_pattern = false;
	get_identity_matrix(&pattern->transform);
	get_identity_matrix(&pattern->inverse);
	pattern->texture[0] = NULL;
	pattern->texture[1] = NULL;
	pattern->texture[2] = NULL;
	pattern->texture[3] = NULL;
	pattern->texture[4] = NULL;
	pattern->texture[5] = NULL;
	pattern->texture_map.uv_pattern.a = NULL;
	pattern->texture_map.uv_pattern.b = NULL;
	pattern->is_tri = false;
	return (pattern);
}

void	set_interpolate_uv(t_pattern *pattern, t_shape *shape)
{
	pattern->uv.u = (1.0 - shape->tri.u - shape->tri.v) * pattern->v1_uv.u
		+ shape->tri.u * pattern->v2_uv.u + shape->tri.v * pattern->v3_uv.u;
	pattern->uv.v = (1.0 - shape->tri.u - shape->tri.v) * pattern->v1_uv.v
		+ shape->tri.u * pattern->v2_uv.v + shape->tri.v * pattern->v3_uv.v;
}

t_color	*pattern_at_shape(t_pattern *pattern, t_shape *shape,
				t_point *world_point, t_color *color)
{
	t_point		shape_point;

	if (shape->is_tri)
		set_interpolate_uv(pattern, shape);
	multiply_matrix_by_tuple(&shape->inverse, world_point, &shape_point);
	pattern->pattern_at(pattern, &shape_point, color);
	return (color);
}

void	set_pattern_transform(t_pattern *pattern, t_matrix *transform)
{
	pattern->transform = *transform;
	inverse_matrix(transform, &pattern->inverse);
}
