#include "tuples.h"
#include "utils.h"

bool	eq_dbl(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}
