#include "groups.h"

void	plane_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape)
		return ;
	tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
		(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
	shape->is_bounds_precal = true;
	shape->bounds = new_bounds(new_point(-MAXFLOAT, 0, -MAXFLOAT),
			new_point(MAXFLOAT, 0, MAXFLOAT));
	get_bounds(shape, &tmp_bounds);
	shape->bounds = tmp_bounds;
	if (shape->left || shape->right)
		get_group_bounds(shape, &tmp_bounds);
	shape->subg_bounds = tmp_bounds;
	shape->split_box[0] = tmp_bounds;
	shape->split_box[1] = tmp_bounds;
	split_bounds(shape->split_box);
}

void	cube_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape)
		return ;
	tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
		(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
	shape->is_bounds_precal = true;
	shape->bounds = new_bounds(new_point(-1, -1, -1),
			new_point(1, 1, 1));
	get_bounds(shape, &tmp_bounds);
	shape->bounds = tmp_bounds;
	if (shape->left || shape->right)
		get_group_bounds(shape, &tmp_bounds);
	shape->subg_bounds = tmp_bounds;
	shape->split_box[0] = tmp_bounds;
	shape->split_box[1] = tmp_bounds;
	split_bounds(shape->split_box);
}

void	cone_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;
	double		limit;

	tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
		(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
	shape->is_bounds_precal = true;
	limit = fmax(fabs(shape->cone.min), fabs(shape->cone.max));
	shape->bounds = new_bounds(new_point(-limit, shape->cone.min, -limit),
			new_point(limit, shape->cone.max, limit));
	get_bounds(shape, &tmp_bounds);
	shape->bounds = tmp_bounds;
	if (shape->left || shape->right)
		get_group_bounds(shape, &tmp_bounds);
	shape->subg_bounds = tmp_bounds;
	shape->split_box[0] = tmp_bounds;
	shape->split_box[1] = tmp_bounds;
	split_bounds(shape->split_box);
}

void	cylinder_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape)
		return ;
	tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
		(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
	shape->is_bounds_precal = true;
	shape->bounds = new_bounds(new_point(-1, shape->cyl.min, -1),
			new_point(1, shape->cyl.max, 1));
	get_bounds(shape, &tmp_bounds);
	shape->bounds = tmp_bounds;
	if (shape->left || shape->right)
		get_group_bounds(shape, &tmp_bounds);
	shape->subg_bounds = tmp_bounds;
	shape->split_box[0] = tmp_bounds;
	shape->split_box[1] = tmp_bounds;
	split_bounds(shape->split_box);
}

void	sphere_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (!shape)
		return ;
	tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
		(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
	shape->is_bounds_precal = true;
	shape->bounds = new_bounds(new_point(-1, -1, -1),
			new_point(1, 1, 1));
	get_bounds(shape, &tmp_bounds);
	shape->bounds = tmp_bounds;
	if (shape->left || shape->right)
		get_group_bounds(shape, &tmp_bounds);
	shape->subg_bounds = tmp_bounds;
	shape->split_box[0] = tmp_bounds;
	shape->split_box[1] = tmp_bounds;
	split_bounds(shape->split_box);
}
