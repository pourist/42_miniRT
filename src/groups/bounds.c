#include "groups.h"

t_bounds	new_bounds(t_point min, t_point max)
{
	return ((t_bounds){min, max});
}

static void	new_box(t_bounds *bounds, t_point box[8])
{
	box[0] = new_point(bounds->max.x, bounds->min.y, bounds->min.z);
	box[1] = new_point(bounds->min.x, bounds->min.y, bounds->min.z);
	box[2] = new_point(bounds->min.x, bounds->min.y, bounds->max.z);
	box[3] = new_point(bounds->max.x, bounds->min.y, bounds->max.z);
	box[4] = new_point(bounds->max.x, bounds->max.y, bounds->min.z);
	box[5] = new_point(bounds->min.x, bounds->max.y, bounds->min.z);
	box[6] = new_point(bounds->min.x, bounds->max.y, bounds->max.z);
	box[7] = new_point(bounds->max.x, bounds->max.y, bounds->max.z);
}

void	get_max_bounds(t_shape *shape)
{
	t_point	box[8];
	int		i;

	new_box(&shape->bounds, box);
	i = -1;
	while (++i < 8)
		box[i] = multiply_matrix_by_tuple(shape->transform, box[i]);
	while (--i >= 0)
	{
		if (box[i].x < shape->bounds.min.x)
			shape->bounds.min.x = box[i].x;
		if (box[i].y < shape->bounds.min.y)
			shape->bounds.min.y = box[i].y;
		if (box[i].z < shape->bounds.min.z)
			shape->bounds.min.z = box[i].z;
		if (box[i].x > shape->bounds.max.x)
			shape->bounds.max.x = box[i].x;
		if (box[i].y > shape->bounds.max.y)
			shape->bounds.max.y = box[i].y;
		if (box[i].z > shape->bounds.max.z)
			shape->bounds.max.z = box[i].z;
	}
}

static t_range	check_axis(double origin, double direction,
					double min, double max)
{
	t_range	t;
	t_range	t_numerator;

	t_numerator.min = (min - origin);
	t_numerator.max = (max - origin);
	if (fabs(direction) >= EPSILON)
	{
		t.min = t_numerator.min / direction;
		t.max = t_numerator.max / direction;
	}
	else
	{
		t.min = t_numerator.min * INFINITY;
		t.max = t_numerator.max * INFINITY;
	}
	if (t.min > t.max)
		ft_swap(&t.min, &t.max);
	return (t);
}

bool	intersect_bounds(t_bounds *b, t_ray *r)
{
	t_range	xt;
	t_range	yt;
	t_range	zt;
	t_range	t;

	xt = check_axis(r->origin.x, r->direction.x, b->min.x, b->max.x);
	yt = check_axis(r->origin.y, r->direction.y, b->min.y, b->max.y);
	zt = check_axis(r->origin.z, r->direction.z, b->min.z, b->max.z);
	t.min = ft_max(xt.min, yt.min, zt.min);
	t.max = ft_min(xt.max, yt.max, zt.max);
	if (t.min > t.max)
		return (false);
	return (true);
}
