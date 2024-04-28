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

/* @brief t_color is a struct that represents a rgb color, 1.0 is
 * the max value, 0.0 is the min value	*/
typedef struct s_color {
	double	r;
	double	g;
	double	b;
	double	a;
}	t_color;

/* Tuples creation functions */
t_tuple		new_tuple(double x, double y, double z, double w);
t_tuple		new_point(double x, double y, double z);
t_tuple		new_vector(double x, double y, double z);

/* Tuples basic math operations */
t_tuple		add(t_tuple t1, t_tuple t2);
t_tuple		subtract(t_tuple t1, t_tuple t2);
t_tuple		negate(t_tuple t);
t_tuple		multiply(t_tuple t, double scalar);
t_tuple		divide(t_tuple t, double scalar);

/* Vector math operations */
double		magnitude_squared(t_vector a);
t_vector	normalize(t_vector a);
double		dot(t_vector a, t_vector b);
t_vector	cross(t_vector a, t_vector b);
t_tuple		reflect(t_vector in, t_vector normal);

/* Color creation  */
t_color		new_color(double r, double g, double b, double a);

/*  Color operations */
t_color		add_color(t_color c1, t_color c2);
t_color		subtract_color(t_color c1, t_color c2);
t_color		multiply_color(t_color c, double scalar);
t_color		hadamard_product(t_color c1, t_color c2);

#endif
