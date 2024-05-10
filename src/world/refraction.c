#include "world.h"

static t_hit	*last(t_hit *xs)
{
	t_hit	*tmp;

	tmp = xs;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static bool	is_included(t_hit **container, t_hit *hit)
{
	t_hit	*tmp;

	tmp = *container;
	while (tmp)
	{
		if (tmp->obj == hit->obj)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void	remove_hit(t_hit **container, t_hit *hit)
{
	t_hit	*tmp;
	t_hit	*prev;

	tmp = *container;
	prev = NULL;
	while (tmp)
	{
		if (tmp->obj == hit->obj)
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

static void	append_hit(t_hit **container, t_hit *hit)
{
	t_hit	*tmp;

	tmp = *container;
	if (!tmp)
	{
		*container = hit;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = hit;
}

void	find_refractive_indices(t_comps *comps, t_hit *i, t_hit *xs)
{
	t_hit	*container; 

	container = NULL;
	while (xs) 
	{
		if (i == xs) 
		{
			if (!container) 
				comps->n1 = 1;
			else
				comps->n1 = last(container)->obj->material.refractive_index;
		}
		if (is_included(&container, xs))
			remove_hit(&container, xs);
		else
			append_hit(&container, xs);
		if (i == xs) 
		{
			if (!container)
				comps->n2 = 1;
			else
				comps->n2 = last(container)->obj->material.refractive_index;
			break ;
		}
		xs = (xs)->next;
	}
}
