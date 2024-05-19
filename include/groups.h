#ifndef GROUPS_H
# define GROUPS_H

# include "shapes.h"

// Group
t_shape		new_group(void);
// Group tree
void		add_child(t_shape *group, t_shape *child);
void		get_group_bounds(t_group **root, t_bounds *b);
void		intersect_group_shapes(t_group **root, t_hit **xs, t_ray *r);
// Bounds
t_bounds	new_bounds(t_point min, t_point max);
bool		intersect_bounds(t_bounds *b, t_ray *r);
void		get_bounds(t_shape *shape, t_bounds *new_bounds);
// Local bounds
void		sphere_bounds(t_shape *shape);
void		cylinder_bounds(t_shape *shape);
void		cone_bounds(t_shape *shape);
void		cube_bounds(t_shape *shape);
void		plane_bounds(t_shape *shape);

#endif
