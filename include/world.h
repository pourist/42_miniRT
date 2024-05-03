#ifndef WORLD_H
# define WORLD_H

# include "shapes.h"
# include "lights.h"

typedef struct s_world
{
	t_hit		*xs;
	int			objs_count;
	t_shape		*objs;
	int			lights_count;
	t_light		*lights;
	t_color		ambient;
}	t_world;

typedef struct s_comps
{
	double			t;
	t_shape			*obj;
	t_point			point;
	t_eye_normal	view;
	t_tuple			over_point;
	t_tuple			under_point;
	t_tuple			reflectv;
	bool			inside;
}	t_comps;

t_world	new_world(void);
t_hit	*intersect_world(t_world *world, t_ray *ray);
t_comps	prepare_computations(t_hit *intersect, t_ray *ray);
t_color	shade_hit(t_world *world, t_comps *comps);
t_color	color_at(t_world *world, t_ray *ray);
// is_shadowed
bool	is_shadowed(t_world *world, t_point *point, int index);

#endif
