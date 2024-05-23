#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <math.h>

# include "tuples.h"
# include "shapes.h"

# define EPSILON	1e-5

/*
The function eq_dbl is used to compare two double values with a precision of
EPSILON (0.00001). It returns true if the two values are equal, false otherwise.
*/
bool	eq_dbl(double a, double b);
double	ft_max(double a, double b, double c);
double	ft_min(double a, double b, double c);
void	ft_swap(double *a, double *b);
double	ft_atof(char *str);

// free

#endif
