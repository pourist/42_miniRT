#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <math.h>

# define EPSILON 0.00001

/*
The function eq_dbl is used to compare two double values with a precision of
EPSILON (0.00001). It returns true if the two values are equal, false otherwise.
*/
bool	eq_dbl(double a, double b);

#endif
