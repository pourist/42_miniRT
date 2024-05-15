#include "shapes.h"

void	cone_discriminant(t_ray *ray, t_discriminant *d)
{
	double	sqrt_d;

	d->a = pow(ray->direction.x, 2) - pow(ray->direction.y, 2)
		+ pow(ray->direction.z, 2);
	d->b = (2.0 * ray->origin.x * ray->direction.x)
		- (2.0 * ray->origin.y * ray->direction.y)
		+ (2.0 * ray->origin.z * ray->direction.z);
	d->c = pow(ray->origin.x, 2) - pow(ray->origin.y, 2)
		+ pow(ray->origin.z, 2);
	d->discriminant = pow(d->b, 2) - 4.0 * d->a * d->c;
	sqrt_d = sqrt(d->discriminant);
	d->t1 = (-d->b - sqrt_d) / (2.0 * d->a);
	d->t2 = (-d->b + sqrt_d) / (2.0 * d->a);
}

void	cylinder_discriminant(t_ray *ray, t_discriminant *d)
{
	double	sqrt_d;

	d->a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	d->b = (2.0 * ray->origin.x * ray->direction.x)
		+ (2.0 * ray->origin.z * ray->direction.z);
	d->c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - 1.0;
	d->discriminant = pow(d->b, 2) - 4.0 * d->a * d->c;
	sqrt_d = sqrt(d->discriminant);
	d->t1 = (-d->b - sqrt_d) / (2.0 * d->a);
	d->t2 = (-d->b + sqrt_d) / (2.0 * d->a);
}
