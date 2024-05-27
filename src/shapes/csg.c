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
	csg->csg.left->parent = csg;
	csg->csg.right->parent = csg;
	csg->intersect_fn = intersect_csg;
	csg->normal_at = normal_at_csg;
	csg->bounds_fn = csg_bounds;
	return (csg);
}

static void	merge_intersections(t_hit **all_xs, t_hit *new_xs)
{
	t_hit	*tmp;

	while (new_xs)
	{
		tmp = new_xs;
		new_xs = new_xs->next;
		tmp->next = NULL;
		insert_intersection(all_xs, tmp);
	}
}

static bool	intersect_csg(t_hit **xs, t_shape *csg, t_ray r)
{
	t_hit	*l_xs; 
	t_hit	*r_xs; 
	t_hit	*all_xs;
	// t_ray	local_ray;

	csg->bounds_fn(csg);
	if (!intersect_bounds(&csg->bounds, &r))
		return (false);
	l_xs = NULL;
	r_xs = NULL;
	all_xs = NULL;
	// local_ray = transform(r, csg->inverse);
	intersect(&l_xs, csg->csg.left, r);
	intersect(&r_xs, csg->csg.right, r);
	merge_intersections(&all_xs, l_xs);
	merge_intersections(&all_xs, r_xs);
	filter_intersections(all_xs, csg, xs);
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
