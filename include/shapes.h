#ifndef SHAPES_H
# define SHAPES_H

# include "rays.h"
# include "materials.h"
# include "patterns.h"
# include "utils.h"

# define MAX_NODES	511

typedef struct s_sphere {
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_plane {
	t_point	origin;
}	t_plane;

typedef struct s_cube {
	t_point	origin;
}	t_cube;

typedef struct s_cylinder {
	t_point	origin;
	double	min;
	double	max;
	bool	closed;
}	t_cylinder;

typedef struct s_cone {
	t_point	origin;
	double	min;
	double	max;
	bool	closed;
}	t_cone;

typedef struct s_hit	t_hit;
typedef struct s_shape	t_shape;
typedef bool			(*t_intersect_fn)(t_hit **, t_shape *, t_ray);
typedef t_tuple			(*t_normal_fn)(t_shape *, t_point);

typedef struct s_shape {
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cube		cube;
		t_cylinder	cyl;
		t_cone		cone;
	};
	t_intersect_fn	intersect_fn;
	t_normal_fn		normal_at;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
	t_material		material;
	bool			cast_shadow;
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
t_shape		new_sphere(void);
t_shape		new_glass_sphere(void);
// Plane Shape
t_shape		new_plane(void);
// Cube Shape
t_shape		new_cube(void);
// Cylinder Shape
t_shape		new_cylinder(void);
// Cone Shape
t_shape		new_cone(void);
// discriminants
void		cone_discriminant(t_ray *ray, t_discriminant *d);
void		cylinder_discriminant(t_ray *ray, t_discriminant *d);
// Intersections general
void		intersect(t_hit **xs, t_shape *s, t_ray r);
t_hit		*intersection(double t, t_shape	*shape);
void		insert_intersection(t_hit **xs, t_hit *hit);
int			intersect_count(t_hit	*xs);
t_hit		*hit(t_hit *xs);
// Shapes
t_shape		new_shape(void);
void		set_transform(t_shape *shape, t_matrix transform);
t_vector	normal_at(t_shape *shape, t_point point);
// Material.c 
t_color		lighting(t_shape *shape, t_light *light, t_point *point,
				t_eye_normal *view);
// pattern.c
t_color		pattern_at_shape(t_pattern *pattern, t_shape *shape,
				t_point *world_point);

#endif
