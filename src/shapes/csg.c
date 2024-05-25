#include "shapes.h"
#include "groups.h"

static bool		intersect_csg(t_hit **xs, t_shape *shape, t_ray r);
static t_vector	normal_at_csg(t_shape *shape, t_point local_point);
static void		csg_bounds(t_shape *shape);

t_shape	*new_csg(t_operation operation, t_shape *left, t_shape *right,
		t_shape *csg)
{
	new_shape(csg);
	csg->is_csg = true;
	csg->csg.op = operation;
	csg->csg.left = left;
	csg->csg.right = right;
	left->parent = csg;
	right->parent = csg;
	csg->intersect_fn = intersect_csg;
	csg->normal_at = normal_at_csg;
	csg->bounds_fn = csg_bounds;
	return (csg);
}

static bool	intersect_csg(t_hit **xs, t_shape *shape, t_ray r)
{
	t_hit	*l_xs; 
	t_hit	*r_xs; 
	t_hit	*tmp;

	shape->bounds_fn(shape);
	if (!intersect_bounds(&shape->bounds, &r))
		return (false);
	l_xs = NULL;
	r_xs = NULL;
	intersect(&l_xs, shape->csg.left, r);
	intersect(&r_xs, shape->csg.right, r);
	while (r_xs)
	{
		tmp = r_xs;
		r_xs = r_xs->next;
		insert_intersection(&l_xs, tmp);
	}
	filter_intersections(l_xs, shape, xs);
	return (true);
}

static t_vector	normal_at_csg(t_shape *shape, t_point local_point)
{
	(void)shape;
	(void)local_point;
	printf("Exception: Attempted to get a normal from a CSG object.\n");
	return ((t_vector){0, 0, 0, 0});
}

static void	csg_bounds(t_shape *shape)
{
	if (!shape->is_bounds_precal)
	{
		shape->is_bounds_precal = true;
		shape->bounds = new_bounds(new_point(INFINITY, INFINITY, INFINITY),
				new_point(-INFINITY, -INFINITY, -INFINITY));
		get_csg_bounds(shape, &shape->bounds);
		get_bounds(shape, &shape->bounds);
	}
}
