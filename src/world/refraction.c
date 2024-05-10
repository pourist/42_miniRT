#include "world.h"

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

static void	remove_hit(t_list **container, t_shape *obj)
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
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_lst(t_list *container)
{
	t_list	*tmp;

	if (!container)
		return ;
	while (container->next)
	{
		tmp = container;
		container = container->next;
		free(tmp);
	}
	free(container);
}

void	find_refractive_indices(t_comps *comps, t_hit *i, t_hit *xs)
{
	t_list	*container;

	container = NULL;
	while (xs) 
	{
		if (i == xs) 
		{
			if (!container) 
				comps->n1 = 1;
			else
				comps->n1 = ((t_shape *)ft_lstlast(container)->content)->material.refractive_index;
		}
		if (xs && is_included(container, xs->obj))
			remove_hit(&container, xs->obj);
		else
			ft_lstadd_back(&container, ft_lstnew(xs->obj));
		if (i == xs) 
		{
			if (!container)
				comps->n2 = 1;
			else
				comps->n2 = ((t_shape *)ft_lstlast(container)->content)->material.refractive_index;
			break ;
		}
		xs = xs->next;
	}
	free_lst(container);
}
