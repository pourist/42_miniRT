#ifndef PATTERNS_H
# define PATTERNS_H

# include "matrices.h"
# include "MLX42/MLX42.h"

typedef struct s_pattern		t_pattern;
typedef struct s_checker		t_checker;
typedef struct s_texture_map	t_texture_map;

typedef t_color					(*t_pattern_at_fn)(t_pattern *, t_point *);
typedef double					*(*t_uv_mapping)(t_point *, double [2]);

typedef struct s_checker
{
	double		width;
	double		height;
	t_pattern	*a;
	t_pattern	*b;
}	t_checker;

typedef struct s_texture_map
{
	t_checker		uv_pattern;
	t_uv_mapping	uv_mapping_fn;
	mlx_texture_t	*texture;
}	t_texture_map;

typedef struct s_pattern
{
	t_pattern		*a;
	t_pattern		*b;
	t_color			color;
	t_pattern_at_fn	pattern_at;
	bool			has_pattern;
	t_matrix		transform;
	t_matrix		inverse;
	t_texture_map	texture_map;
}	t_pattern;

t_pattern	*new_pattern(t_pattern *pattern);
t_pattern	new_solid_pattern(t_color color);
void		set_pattern_transform(t_pattern *pattern, t_matrix *transform);
// Patterns
t_pattern	*new_stripe_pattern(t_pattern a, t_pattern b, t_pattern *pattern);
t_pattern	*new_gradient_pattern(t_pattern a, t_pattern b, t_pattern *pattern);
t_pattern	*new_ring_pattern(t_pattern a, t_pattern b, t_pattern *pattern);
t_pattern	*new_checkers_pattern(t_pattern a, t_pattern b, t_pattern *pattern);
t_pattern	*new_uv_checkers_pattern(t_pattern a, t_pattern b,
				t_pattern *pattern);
t_pattern	*new_full_gradient_pattern(t_pattern a, t_pattern b,
				t_pattern *pattern);
t_pattern	*new_radial_gradient_pattern(t_pattern a, t_pattern b,
				t_pattern *pattern);
t_pattern	*new_blended_pattern(t_pattern a, t_pattern b, t_pattern *pattern);
// texture_mapping
t_checker	uv_checkers(double width, double height, t_pattern *a,
				t_pattern *b);
t_pattern	*uv_pattern_at(t_checker *checkers, double *u, double *v);
void		texture_map(t_pattern *pattern, t_checker *checkers,
				t_uv_mapping uv_mapping_fn);
double		*spherical_map(t_point *point, double uv[2]);
double		*planar_map(t_point *point, double uv[2]);
double		*cylindrical_map(t_point *point, double uv[2]);

#endif
