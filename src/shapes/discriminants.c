#include "shapes.h"

void	cone_discriminant(t_ray *ray, t_intersect_params *p)
{
	double	sqrt_d;

	p->a = (ray->direction.x * ray->direction.x)
		- (ray->direction.y * ray->direction.y)
		+ (ray->direction.z * ray->direction.z);
	p->b = (2.0 * ray->origin.x * ray->direction.x)
		- (2.0 * ray->origin.y * ray->direction.y)
		+ (2.0 * ray->origin.z * ray->direction.z);
	p->c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y)
		+ (ray->origin.z * ray->origin.z);
	p->discriminant = pow(p->b, 2) - 4.0 * p->a * p->c;
	sqrt_d = sqrt(p->discriminant);
	p->t1 = (-p->b - sqrt_d) / (2.0 * p->a);
	p->t2 = (-p->b + sqrt_d) / (2.0 * p->a);
}

void	cylinder_discriminant(t_ray *ray, t_intersect_params *p)
{
	double	sqrt_d;

	p->a = (ray->direction.x * ray->direction.x)
		+ (ray->direction.z * ray->direction.z);
	p->b = (2.0 * ray->origin.x * ray->direction.x)
		+ (2.0 * ray->origin.z * ray->direction.z);
	p->c = (ray->origin.x * ray->origin.x)
		+ (ray->origin.z * ray->origin.z) - 1.0;
	p->discriminant = pow(p->b, 2) - 4.0 * p->a * p->c;
	sqrt_d = sqrt(p->discriminant);
	p->t1 = (-p->b - sqrt_d) / (2.0 * p->a);
	p->t2 = (-p->b + sqrt_d) / (2.0 * p->a);
}
