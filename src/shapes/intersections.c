#include "shapes.h"

void	intersect(t_hit **xs, t_shape *s, t_ray r)
{
	s->intersect_fn(xs, s, r);
}

t_hit	*intersection(double t, t_shape	*shape)
{
	static t_hit	pool[MAX_NODES];
	static size_t	index = 0;
	t_hit			*hit;

	hit = &pool[index++ % MAX_NODES];
	hit->t = t;
	hit->obj = shape;
	hit->next = NULL;
	return (hit);
}

void	insert_intersection(t_hit **xs, t_hit *hit)
{
	t_hit	*current;
	t_hit	*prev;

	if (*xs == NULL)
		*xs = hit;
	else
	{
		current = *xs;
		prev = NULL;
		while (current && current->t < hit->t)
		{
			prev = current;
			current = current->next;
		}
		if (prev)
		{
			prev->next = hit;
			hit->next = current;
		}
		else
		{
			hit->next = *xs;
			*xs = hit;
		}
	}
}

int	intersect_count(t_hit	*xs)
{
	int	count;

	count = 0;
	while (xs)
	{
		count++;
		xs = xs->next;
	}
	return (count);
}

t_hit	*hit(t_hit *xs)
{
	while (xs != NULL && xs->t < EPSILON)
		xs = xs->next;
	return (xs);
}
