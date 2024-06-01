#include "test.h"

bool	matrix_eq(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	if (a.size != b.size)
		return (false);
	i = -1;
	while (++i < a.size)
	{
		j = -1;
		while (++j < a.size)
			if (a.mx[i][j] - b.mx[i][j] > EPSILON
				|| a.mx[i][j] - b.mx[i][j] < -EPSILON)
				return (false);
	}
	return (true);
}

bool	tuple_eq(t_tuple a, t_tuple b)
{
	if (a.x - b.x > EPSILON || a.x - b.x < -EPSILON)
		return (false);
	if (a.y - b.y > EPSILON || a.y - b.y < -EPSILON)
		return (false);
	if (a.z - b.z > EPSILON || a.z - b.z < -EPSILON)
		return (false);
	if (a.w - b.w > EPSILON || a.w - b.w < -EPSILON)
		return (false);
	return (true);
}

bool	color_eq(t_color a, t_color b)
{
	if (a.r - b.r > EPSILON || a.r - b.r < -EPSILON)
		return (false);
	if (a.g - b.g > EPSILON || a.g - b.g < -EPSILON)
		return (false);
	if (a.b - b.b > EPSILON || a.b - b.b < -EPSILON)
		return (false);
	return (true);
}

t_world	default_world(void)
{
	t_world	w;

	w = new_world();
	w.ambient = new_color(0, 0, 0);
	w.objs = malloc(sizeof(t_shape) * 2);
	w.objs_count = 2;
	new_sphere(&w.objs[0]);
	w.objs[0].material.color = new_color(0.8, 1.0, 0.6);
	w.objs[0].material.diffuse = 0.7;
	w.objs[0].material.specular = 0.2;
	new_sphere(&w.objs[1]);
	set_transform(&(w.objs[1]), scaling(0.5, 0.5, 0.5));
	w.lights = malloc(sizeof(t_light));
	w.lights_count = 1;
	w.lights[0] = new_light(new_point(-10, 10, -10), new_color(1, 1, 1));
	return (w);
}

static t_color	test_at(t_pattern *pattern, t_point *shape_point);

t_pattern	new_test_pattern(void)
{
	t_pattern	test;

	test = new_pattern();
	test.pattern_at = test_at;
	test.has_pattern = true;
	return (test);
}

static t_color	test_at(t_pattern *pattern, t_point *shape_point)
{
	(void)pattern;
	return (new_color(shape_point->x, shape_point->y, shape_point->z));
}

void	new_test_shape(t_shape *shape)
{
	new_shape(shape);
	shape->bounds = new_bounds(new_point(-1, -1, -1), new_point(1, 1, 1));
}
