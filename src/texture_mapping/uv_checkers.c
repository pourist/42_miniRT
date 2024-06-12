#include "patterns.h"

t_checker	uv_checkers(double width, double height, t_pattern *a,
				t_pattern *b)
{
	return ((t_checker){width, height, a, b});
}

t_pattern	*uv_pattern_at(t_checker *checkers, double *u, double *v)
{
	int	u2;
	int	v2;

	u2 = (int)(*u * checkers->width);
	v2 = (int)(*v * checkers->height);
	if (((u2 + v2) & 1) == 0)
		return (checkers->a);
	else
		return (checkers->b);
}

void	texture_map(t_pattern *pattern, t_checker *checkers,
		t_uv_mapping uv_mapping_fn)
{
	pattern->texture_map.uv_pattern = *checkers;
	pattern->texture_map.uv_mapping_fn = uv_mapping_fn;
}

double	*spherical_map(t_point *point, double uv[2])
{
	double		theta;
	t_vector	vec;
	double		radius;
	double		phi;
	double		raw_u;

	theta = atan2(point->x, point->z);
	new_vector(point->x, point->y, point->z, &vec);
	radius = sqrt(magnitude_squared(&vec));
	phi = acos(point->y / radius);
	raw_u = theta / (2 * M_PI);
	uv[0] = 1 - (raw_u + 0.5);
	uv[1] = 1 - phi / M_PI;
	return (uv);
}

double	*planar_map(t_point *point, double uv[2])
{
	uv[1] = fmod(point->z, 1);
	uv[0] = fmod(point->x, 1);
	if (uv[1] < 0)
		uv[1] = 1 + uv[1];
	if (uv[0] < 0)
		uv[0] = 1 + uv[0];
	return (uv);
}

double	*cylindrical_map(t_point *point, double uv[2])
{
	double	theta;
	double	raw_u;

	theta = atan2(point->x, point->z);
	raw_u = theta / (2 * M_PI);
	uv[0] = 1 - (raw_u + 0.5);
	uv[1] = fmod(point->y, 1);
	if (uv[1] < 0)
		uv[1] = 1 + uv[1];
	return (uv);
}
