#include "shapes.h"

void	cone_discriminant(t_ray *ray, t_intersect_params *p)
{
	double	sqrt_d;

	p->a = pow(ray->direction.x, 2) - pow(ray->direction.y, 2)
		+ pow(ray->direction.z, 2);
	p->b = (2.0 * ray->origin.x * ray->direction.x)
		- (2.0 * ray->origin.y * ray->direction.y)
		+ (2.0 * ray->origin.z * ray->direction.z);
	p->c = pow(ray->origin.x, 2) - pow(ray->origin.y, 2)
		+ pow(ray->origin.z, 2);
	p->discriminant = pow(p->b, 2) - 4.0 * p->a * p->c;
	sqrt_d = sqrt(p->discriminant);
	p->t1 = (-p->b - sqrt_d) / (2.0 * p->a);
	p->t2 = (-p->b + sqrt_d) / (2.0 * p->a);
}

void	cylinder_discriminant(t_ray *ray, t_intersect_params *p)
{
	double	sqrt_d;

	p->a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	p->b = (2.0 * ray->origin.x * ray->direction.x)
		+ (2.0 * ray->origin.z * ray->direction.z);
	p->c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - 1.0;
	p->discriminant = pow(p->b, 2) - 4.0 * p->a * p->c;
	sqrt_d = sqrt(p->discriminant);
	p->t1 = (-p->b - sqrt_d) / (2.0 * p->a);
	p->t2 = (-p->b + sqrt_d) / (2.0 * p->a);
}
