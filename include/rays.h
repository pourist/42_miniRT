#ifndef RAYS_H
# define RAYS_H

# include "tuples.h"

typedef struct s_ray {
	t_point		origin;
	t_vector	direction;
}	t_ray;

t_ray	new_ray(t_point	origin, t_point	direction);
t_point	position(t_ray r, double t);

#endif
