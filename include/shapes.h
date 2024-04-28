#ifndef SHAPES_H
# define SHAPES_H

# include "tuples.h"
# include "rays.h"
# include "matrices.h"

# define MAX_NODES	512
# define EPSILON	1e-5

typedef struct s_sphere {
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_hit	t_hit;
typedef struct s_shape	t_shape;
typedef bool			(*t_intersect_fn)(t_hit **, t_shape *, t_ray);

typedef struct s_shape {
	union {
		t_sphere	sphere;
	};
	t_intersect_fn	intersect_fn;
	t_matrix		transform;
	t_matrix		inverse;
}	t_shape;

typedef struct s_hit {
	double	t;
	t_shape	*obj;
	t_hit	*next;
}	t_hit;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	discriminant;
}	t_discriminant;

// Sphere Shape
t_shape	new_sphere(void);
bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray);

// Intersections general
void	intersect(t_hit **xs, t_shape *s, t_ray r);
t_hit	*intersection(double t, t_shape	*shape);
void	insert_intersection(t_hit **xs, t_hit *hit);
int		intersect_count(t_hit	*xs);
t_hit	*hit(t_hit *xs);

// Shapes utils
t_shape	new_shape(void);
void	set_transform(t_shape *shape, t_matrix transform);

#endif
