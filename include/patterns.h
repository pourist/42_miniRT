#ifndef PATTERNS_H
# define PATTERNS_H

# include "matrices.h"

typedef struct s_pattern	t_pattern;
typedef t_color				(*t_pattern_at_fn)(t_pattern *, t_point *);

typedef struct s_pattern
{
	t_color			a;
	t_color			b;
	t_pattern_at_fn	pattern_at;
	bool			has_pattern;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
}	t_pattern;

t_pattern	new_pattern(void);
void		set_pattern_transform(t_pattern *pattern, t_matrix transform);
// Patterns
t_pattern	new_stripe_pattern(t_color a, t_color b);
t_pattern	new_gradient_pattern(t_color a, t_color b);
t_pattern	new_ring_pattern(t_color a, t_color b);
t_pattern	new_checkers_pattern(t_color a, t_color b);

#endif
