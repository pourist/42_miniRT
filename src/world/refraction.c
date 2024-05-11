#include "world.h"

t_color	refracted_color(t_world *world, t_comps *comps)
{
	double		n_ratio;
	double		cos_i;
	double		sin2_t;
	double		cos_t;
	t_vector	direction;
	t_ray			refract_ray;
	t_color		refracted_color;

	(void)world;
	if (world->remaining_recursion == 0 || comps->obj->material.transparency == 0)
		return (new_color(0, 0, 0));
	n_ratio = comps->n1 / comps->n2;
	cos_i = dot(comps->view.eye_v, comps->view.normal_v);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1)
		return (new_color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	direction = subtract(
			multiply(comps->view.normal_v, (n_ratio * cos_i - cos_t)),
			multiply(comps->view.eye_v, n_ratio));
	refract_ray = new_ray(comps->under_point, direction);
	world->remaining_recursion--;
	refracted_color = color_at(world, &refract_ray);
	return (multiply_color(refracted_color, comps->obj->material.transparency));
}

static bool	is_included(t_list *container, t_shape *obj)
{
	t_list	*tmp;

	tmp = container;
	while (tmp)
	{
		if (tmp->content == obj)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void	remove_obj(t_list **container, t_shape *obj)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *container;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content == obj)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*container = tmp->next;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static t_list	*new_lst(t_shape *shape)
{
	static t_list	pool[MAX_NODES + 1];
	static size_t	index = 0;
	t_list			*node;

	node = &pool[index++ & (MAX_NODES)];
	node->content = shape;
	node->next = NULL;
	return (node);
}

static void	set_indices(t_list *container, double *n)
{
	if (!container) 
		*n = 1;
	else
		*n = ((t_shape *)ft_lstlast(container)
				->content)->material.refractive_index;
}

void	find_refractive_indices(t_comps *comps, t_hit *i, t_hit *xs)
{
	t_list	*container;

	container = NULL;
	while (xs) 
	{
		if (i == xs) 
			set_indices(container, &comps->n1);
		if (xs && is_included(container, xs->obj))
			remove_obj(&container, xs->obj);
		else
			ft_lstadd_back(&container, new_lst(xs->obj));
		if (i == xs) 
		{
			set_indices(container, &comps->n2);
			break ;
		}
		xs = xs->next;
	}
}
