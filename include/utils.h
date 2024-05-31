#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <math.h>

# include "libft.h"
# include "tuples.h"
// # include "shapes.h"

# define EPSILON	1e-5
# define MAX_SEQUENCER 8
# define MAX_SEQ_VALUES 8

typedef struct s_sequencer
{
	int		base;
	int		index;
}	t_sequencer;

/*
The function eq_dbl is used to compare two double values with a precision of
EPSILON (0.00001). It returns true if the two values are equal, false otherwise.
*/
bool		eq_dbl(double a, double b);
double		ft_max(double a, double b, double c);
double		ft_min(double a, double b, double c);
void		ft_swap(double *a, double *b);
double		ft_atof(char *str);
void		new_sequencer(t_sequencer *gen);
double		halton_sequence(t_sequencer *gen);
double		next_sequence(t_sequencer *gen);

#endif
