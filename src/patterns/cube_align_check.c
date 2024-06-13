#include "patterns.h"

static t_color	uv_align_check_at(t_pattern *pattern, t_point *shape_point);
static t_color	uv_cube_align_check_map_at(t_pattern *pattern,
					t_point *shape_point);

t_pattern	*new_uv_align_check_pattern(t_pattern *pattern, t_color color[5])
{
	if (!pattern)
		return (NULL);
	pattern->pattern_at = uv_align_check_at;
	pattern->has_pattern = true;
	pattern->align_colors.main = color[0];
	pattern->align_colors.ul = color[1];
	pattern->align_colors.ur = color[2];
	pattern->align_colors.bl = color[3];
	pattern->align_colors.br = color[4];
	return (pattern);
}

t_pattern	*new_cube_align_check_pattern(t_pattern *pattern, t_pattern faces[6])
{
	if (!pattern)
		return (NULL);
	pattern->a = malloc(6 * sizeof(t_pattern));
	if (!pattern->a)
		return (pattern);
	pattern->a[0] = faces[0];
	pattern->a[1] = faces[1];
	pattern->a[2] = faces[2];
	pattern->a[3] = faces[3];
	pattern->a[4] = faces[4];
	pattern->a[5] = faces[5];
	pattern->pattern_at = uv_cube_align_check_map_at;
	pattern->has_pattern = true;
	return (pattern);
}

static t_color	uv_texture_map_at(t_pattern *pattern, t_point *shape_point);

t_pattern	*new_texture_map(t_pattern *pattern, char const *path)
{
	if (!pattern)
		return (NULL);
	pattern->texture = mlx_load_png(path);
	if (!pattern->texture)
		return (NULL);
	pattern->has_pattern = true;
	pattern->pattern_at = uv_texture_map_at;
	return (pattern);
}

static t_color	uv_texture_map_at(t_pattern *pattern, t_point *shape_point)
{
	t_point		pattern_point;
	double		uv[2];
	t_color		color;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	pattern->texture_map.uv_mapping_fn(&pattern_point, uv);
	uv_texture_color_at(pattern->texture, &uv[0], &uv[1], &color);
	return (color);
}

static t_color	uv_align_check_at(t_pattern *pattern, t_point *shape_point)
{
	t_point		pattern_point;
	double		uv[2];
	t_color		color;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	pattern->texture_map.uv_mapping_fn(&pattern_point, uv);
	color = uv_pattern_color_at(&pattern->align_colors, &uv[0], &uv[1]);
	return (color);
}

static t_color	uv_cube_align_check_map_at(t_pattern *pattern,
					t_point *shape_point)
{
	t_point		pattern_point;
	double		uv[2];
	t_color		color;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	pattern->texture_map.uv_mapping_fn(&pattern_point, uv);
	color = uv_pattern_color_at(&pattern->a[face_from_point(&pattern_point)]
			.align_colors, &uv[0], &uv[1]);
	return (color);
}
