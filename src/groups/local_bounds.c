#include "groups.h"

void	plane_bounds(t_shape *shape)
{
	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-INFINITY, 0, -INFINITY),
				new_point(INFINITY, 0, INFINITY));
		get_max_bounds(shape);
	}
}

void	cube_bounds(t_shape *shape)
{
	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, -1, -1),
				new_point(1, 1, 1));
		get_max_bounds(shape);
	}
}

void	cone_bounds(t_shape *shape)
{
	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, shape->cone.min, -1),
				new_point(1, shape->cone.max, 1));
		get_max_bounds(shape);
	}
}

void	cylinder_bounds(t_shape *shape)
{
	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, shape->cyl.min, -1),
				new_point(1, shape->cyl.max, 1));
		get_max_bounds(shape);
	}
}

void	sphere_bounds(t_shape *shape)
{
	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(-1, -1, -1),
				new_point(1, 1, 1));
		get_max_bounds(shape);
	}
}
