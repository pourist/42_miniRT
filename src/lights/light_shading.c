#include "world.h"
#include "lights.h"

static t_color	*darken(t_material *m, t_lighting_params *lp);
static t_color	*lighten(t_material *m, t_lighting_params *lp, t_light *light,
					t_eye_normal *view);

t_color	area_lighting(t_shape *s, t_light *l, t_point *p, t_eye_normal *v)
{
	t_lighting_params	lp;
	int					i[2];
	t_point				tmp;

	prepare_material(&lp, s, p, v);
	hadamard_product(&lp.color, &l->intensity, &lp.effective_color);
	new_color(0, 0, 0, &lp.t_color);
	i[1] = -1;
	while (++i[1] < l->vsteps)
	{
		i[0] = -1;
		while (++i[0] < l->usteps)
		{
			normalize(subtract(point_on_light(l, i[0], i[1], &tmp),
					p, &tmp), &lp.light_v);
			lp.light_dot_normal = dot(&lp.light_v, &v->normal_v);
			if (lp.light_dot_normal < 0 || l->intensity_ratio <= 0)
				add_color(&lp.t_color, darken(&s->material, &lp), &lp.t_color);
			else
				add_color(&lp.t_color, lighten(&s->material, &lp, l, v),
					&lp.t_color);
		}
	}
	multiply_color(&lp.t_color, l->inverse_samples, &lp.t_color);
	return (lp.t_color);
}

t_color	lighting(t_shape *shape, t_light *light, t_point *point,
	t_eye_normal *view)
{
	t_lighting_params	lp;

	prepare_material(&lp, shape, point, view);
	hadamard_product(&lp.color, &light->intensity, &lp.effective_color);
	normalize(subtract(&light->position, point, &lp.light_v), &lp.light_v);
	lp.light_dot_normal = dot(&lp.light_v, &view->normal_v);
	if (lp.light_dot_normal < 0 || light->intensity_ratio <= 0)
		darken(&shape->material, &lp);
	else
		lighten(&shape->material, &lp, light, view);
	return (lp.color);
}

static t_color	*darken(t_material *m, t_lighting_params *lp)
{
	hadamard_product(&lp->effective_color, &m->ambient, &lp->ambient);
	new_color(0, 0, 0, &lp->diffuse);
	new_color(0, 0, 0, &lp->specular);
	return (add_color(&lp->ambient, add_color(
				&lp->diffuse, &lp->specular, &lp->color), &lp->color));
}

static t_color	*lighten(t_material *m, t_lighting_params *lp, t_light *light,
					t_eye_normal *view)
{
	hadamard_product(&lp->effective_color, &m->ambient, &lp->ambient);
	multiply_color(&lp->effective_color,
		m->diffuse * lp->light_dot_normal, &lp->diffuse);
	reflect(negate(&lp->light_v, &lp->light_v), &view->normal_v,
		&lp->reflect_v);
	lp->reflect_dot_eye = dot(&lp->reflect_v, &view->eye_v);
	if (lp->reflect_dot_eye <= 0)
		new_color(0, 0, 0, &lp->specular);
	else
		multiply_color(&light->intensity, m->specular
			* pow(lp->reflect_dot_eye, m->shininess), &lp->specular);
	return (add_color(&lp->ambient, multiply_color(add_color(
					&lp->diffuse, &lp->specular, &lp->color),
				light->intensity_ratio, &lp->color), &lp->color));
}
