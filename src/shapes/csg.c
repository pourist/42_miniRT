#include "shapes.h"

t_shape	*new_csg(t_operation operation, t_shape *left, t_shape *right,
		t_shape *csg)
{
	new_shape(csg);
	csg->is_csg = true;
	csg->csg.operation = operation;
	csg->csg.left = left;
	csg->csg.right = right;
	left->parent = csg;
	right->parent = csg;
	return (csg);
}

bool	intersect_allowed(t_operation op, bool lhit, bool inl, bool inr)
{
	if (op == UNION)
		return ((lhit && !inr) || (!lhit && !inl));
	if (op == INTERSECT)
		return ((lhit && inr) || (!lhit && inl));
	if (op == DIFFERENCE)
		return ((lhit && !inr) || (!lhit && inl));
	return (false);
}
