#ifndef TUPLES_H
# define TUPLES_H

# include <stdlib.h>
# include <math.h>

/*  
* @breif t_tuple is a struct that represents a point or a vector in 3D space
*	@param x : x-axis coordinate
*	@param y : y-axis coordinate
*	@param z : z-axis coordinate
*	@param w : Distinguish between point and vector. 1 for point, 0 for vector
*/
typedef struct s_tuple {
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

/* @brief the type t_point is an alias for t_tuple who has w = 1 */
typedef t_tuple	t_point;
/* @brief the type t_vector is an alias for t_tuple who has w = 0 */
typedef t_tuple	t_vector;

/* Tuples creation functions */
t_tuple		tuple(double x, double y, double z, double w);
t_tuple		point(double x, double y, double z);
t_tuple		vector(double x, double y, double z);

/* Tuples basic math operations */
t_tuple		add(t_tuple t1, t_tuple t2);
t_tuple		subtract(t_tuple t1, t_tuple t2);
t_tuple		negate(t_tuple t);
t_tuple		multiply(t_tuple t, double scalar);
t_tuple		division(t_tuple t, double scalar);

/* Vector math operations */
double		magnitude(t_vector v);
t_vector	normalize(t_vector v);
double		dot(t_vector a, t_vector b);
t_vector	cross(t_vector a, t_vector b);

#endif
