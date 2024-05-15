#include "shapes.h"

static bool		intersect_cube(t_hit **xs, t_shape *cube, t_ray r);
static t_vector	normal_at_cube(t_shape *cube, t_point local_point);

t_shape	new_cube(void)
{
	t_shape	shape; 

	shape = new_shape();
	shape.cube.origin = new_point(0, 0, 0);
	shape.intersect_fn = intersect_cube;
	shape.normal_at = normal_at_cube;
	return (shape);
}

static void	check_axis(double origin, double direction,
				double t_min_max[2])
{
	double	t_min_numerator;
	double	t_max_numerator;

	t_min_numerator = (-1 - origin);
	t_max_numerator = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		t_min_max[0] = t_min_numerator / direction;
		t_min_max[1] = t_max_numerator / direction;
	}
	else
	{
		t_min_max[0] = t_min_numerator * INFINITY;
		t_min_max[1] = t_max_numerator * INFINITY;
	}
	if (t_min_max[0] > t_min_max[1])
		ft_swap(&t_min_max[0], &t_min_max[1]);
}

static bool	intersect_cube(t_hit **xs, t_shape *cube, t_ray r)
{
	double	xt_min_max[2];
	double	yt_min_max[2];
	double	zt_min_max[2];
	double	t_min;
	double	t_max;

	check_axis(r.origin.x, r.direction.x, xt_min_max);
	check_axis(r.origin.y, r.direction.y, yt_min_max);
	check_axis(r.origin.z, r.direction.z, zt_min_max);
	t_min = ft_max(xt_min_max[0], yt_min_max[0], zt_min_max[0]);
	t_max = ft_min(xt_min_max[1], yt_min_max[1], zt_min_max[1]);
	if (t_min > t_max)
		return (false);
	insert_intersection(xs, intersection(t_min, cube));
	insert_intersection(xs, intersection(t_max, cube));
	return (true);
}

static t_vector	normal_at_cube(t_shape *cube, t_point local_point)
{
	double	maxc;
	double	absx;
	double	absy;
	double	absz;

	(void)cube;
	absx = fabs(local_point.x);
	absy = fabs(local_point.y);
	absz = fabs(local_point.z);
	maxc = ft_max(absx, absy, absz);
	if (maxc == absx)
		return (new_vector(local_point.x, 0, 0));
	if (maxc == absy)
		return (new_vector(0, local_point.y, 0));
	return (new_vector(0, 0, local_point.z));
}
