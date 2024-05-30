#include "utils.h"

void	new_sequencer(t_sequencer *gen)
{
	static int	base = 1;

	gen->base = ++base;
	gen->index = 0;
}

double	halton_sequence(t_sequencer *gen)
{
	double	result;
	double	f;
	int		i;

	result = 0.0;
	f = 1.0 / gen->base;
	i = ++gen->index;
	while (i > 0)
	{
		result += f * (i % gen->base);
		i /= gen->base;
		f /= gen->base;
	}
	return (result);
}
