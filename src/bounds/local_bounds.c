#include "groups.h"

void	plane_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (shape && !shape->is_bounds_precal)
	{
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		shape->is_bounds_precal = true;
		shape->bounds = (t_bounds){(t_point){-MAXFLOAT, 0, -MAXFLOAT, 1},
			(t_point){MAXFLOAT, 0, MAXFLOAT, 1}};
		get_bounds(shape, &tmp_bounds);
	}
	if (shape && !shape->is_gbounds_precal && shape->next)
	{
		shape->is_gbounds_precal = true;
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		get_group_bounds(shape, &tmp_bounds);
		shape->subg_bounds = tmp_bounds;
		shape->split_box[0] = tmp_bounds;
		shape->split_box[1] = tmp_bounds;
		split_bounds(shape->split_box);
	}
}

void	cube_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (shape && !shape->is_bounds_precal)
	{
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		shape->is_bounds_precal = true;
		shape->bounds = (t_bounds){(t_point){-1, -1, -1, 1},
			(t_point){1, 1, 1, 1}};
		get_bounds(shape, &tmp_bounds);
	}
	if (shape && !shape->is_gbounds_precal && shape->next)
	{
		shape->is_gbounds_precal = true;
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		get_group_bounds(shape, &tmp_bounds);
		shape->subg_bounds = tmp_bounds;
		shape->split_box[0] = tmp_bounds;
		shape->split_box[1] = tmp_bounds;
		split_bounds(shape->split_box);
	}
}

void	cone_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;
	double		limit;

	if (shape && !shape->is_bounds_precal)
	{
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		shape->is_bounds_precal = true;
		limit = fmax(fabs(shape->cone.min), fabs(shape->cone.max));
		shape->bounds = (t_bounds){(t_point){-limit, shape->cone.min, -limit, 1},
			(t_point){limit, shape->cone.max, limit, 1}};
		get_bounds(shape, &tmp_bounds);
	}
	if (shape && !shape->is_gbounds_precal && shape->next)
	{
		shape->is_gbounds_precal = true;
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		get_group_bounds(shape, &tmp_bounds);
		shape->subg_bounds = tmp_bounds;
		shape->split_box[0] = tmp_bounds;
		shape->split_box[1] = tmp_bounds;
		split_bounds(shape->split_box);
	}
}

void	cylinder_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (shape && !shape->is_bounds_precal)
	{
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		shape->is_bounds_precal = true;
		shape->bounds = (t_bounds){(t_point){-1, shape->cyl.min, -1, 1},
			(t_point){1, shape->cyl.max, 1, 1}};
		get_bounds(shape, &tmp_bounds);
	}
	if (shape && !shape->is_gbounds_precal && shape->next)
	{
		shape->is_gbounds_precal = true;
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		get_group_bounds(shape, &tmp_bounds);
		shape->subg_bounds = tmp_bounds;
		shape->split_box[0] = tmp_bounds;
		shape->split_box[1] = tmp_bounds;
		split_bounds(shape->split_box);
	}
}

void	sphere_bounds(t_shape *shape)
{
	t_bounds	tmp_bounds;

	if (shape && !shape->is_bounds_precal)
	{
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		shape->is_bounds_precal = true;
		shape->bounds = (t_bounds){(t_point){-1, -1, -1, 1},
			(t_point){1, 1, 1, 1}};
		get_bounds(shape, &tmp_bounds);
	}
	if (shape && !shape->is_gbounds_precal && shape->next)
	{
		shape->is_gbounds_precal = true;
		tmp_bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1.0},
			(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1.0}};
		get_group_bounds(shape, &tmp_bounds);
		shape->subg_bounds = tmp_bounds;
		shape->split_box[0] = tmp_bounds;
		shape->split_box[1] = tmp_bounds;
		split_bounds(shape->split_box);
	}
}
