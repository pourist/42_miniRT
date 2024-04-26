#ifndef SHAPES_H
# define SHAPES_H

# include "tuples.h"
# include "rays.h"
# include "matrices.h"

typedef struct s_sphere {
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_intersect {
	double		t[2];
	int			count;
}	t_intersect;

typedef struct s_shape {
	union {
		t_sphere	sphere;
	};
}	t_shape;

t_shape	new_sphere(void);
void	intersect(t_intersect *xs, t_shape *s, t_ray ray);

#endif
