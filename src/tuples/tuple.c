#include "tuples.h"

t_tuple	new_tuple(double x, double y, double z, double w)
{
	return ((t_tuple){x, y, z, w});
}

t_tuple	new_point(double x, double y, double z)
{
	return ((t_point){x, y, z, 1.0});
}

t_tuple	new_vector(double x, double y, double z)
{
	return ((t_vector){x, y, z, 0.0});
}
