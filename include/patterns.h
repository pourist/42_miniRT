#ifndef PATTERNS_H
# define PATTERNS_H

# include "matrices.h"

typedef struct s_pattern	t_pattern;
typedef t_color				(*t_pattern_at_fn)(t_pattern *, t_point *);

typedef struct s_pattern
{
	t_pattern		*a;
	t_pattern		*b;
	t_color			color;
	t_pattern_at_fn	pattern_at;
	bool			has_pattern;
	t_matrix		transform;
	t_matrix		inverse;
}	t_pattern;

t_pattern	*new_pattern(t_pattern *pattern);
t_pattern	new_solid_pattern(t_color color);
void		set_pattern_transform(t_pattern *pattern, t_matrix *transform);
// Patterns
t_pattern	new_stripe_pattern(t_pattern a, t_pattern b);
t_pattern	new_gradient_pattern(t_pattern a, t_pattern b);
t_pattern	new_ring_pattern(t_pattern a, t_pattern b);
t_pattern	new_checkers_pattern(t_pattern a, t_pattern b);
t_pattern	new_full_gradient_pattern(t_pattern a, t_pattern b);
t_pattern	new_radial_gradient_pattern(t_pattern a, t_pattern b);
t_pattern	new_blended_pattern(t_pattern a, t_pattern b);

#endif
