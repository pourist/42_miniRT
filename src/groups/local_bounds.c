#include "groups.h"

void	plane_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-INFINITY, 0, -INFINITY),
				new_point(INFINITY, 0, INFINITY));
		tmp_bounds = new_bounds(new_point(INFINITY, INFINITY, INFINITY),
				new_point(-INFINITY, -INFINITY, -INFINITY));
		get_bounds(shape, &tmp_bounds);
		shape->bounds = tmp_bounds;
	}
}

void	cube_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, -1, -1),
				new_point(1, 1, 1));
		tmp_bounds = new_bounds(new_point(INFINITY, INFINITY, INFINITY),
				new_point(-INFINITY, -INFINITY, -INFINITY));
		get_bounds(shape, &tmp_bounds);
		shape->bounds = tmp_bounds;
	}
}

void	cone_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, shape->cone.min, -1),
				new_point(1, shape->cone.max, 1));
		tmp_bounds = new_bounds(new_point(INFINITY, INFINITY, INFINITY),
				new_point(-INFINITY, -INFINITY, -INFINITY));
		get_bounds(shape, &tmp_bounds);
		shape->bounds = tmp_bounds;
	}
}

void	cylinder_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, shape->cyl.min, -1),
				new_point(1, shape->cyl.max, 1));
		tmp_bounds = new_bounds(new_point(INFINITY, INFINITY, INFINITY),
				new_point(-INFINITY, -INFINITY, -INFINITY));
		get_bounds(shape, &tmp_bounds);
		shape->bounds = tmp_bounds;
	}
}

void	sphere_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, -1, -1),
				new_point(1, 1, 1));
		tmp_bounds = new_bounds(new_point(INFINITY, INFINITY, INFINITY),
				new_point(-INFINITY, -INFINITY, -INFINITY));
		get_bounds(shape, &tmp_bounds);
		shape->bounds = tmp_bounds;
	}
}
