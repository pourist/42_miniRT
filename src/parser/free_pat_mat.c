#include "parser.h"

void	free_material(t_material	**material)
{
	int	i;

	i = 0;
	if (!material)
		return ;
	while (material[i])
	{
		if (material[i]->name)
			free(material[i]->name);
		free(material[i++]);
	}
	free(material);
}

void	free_pattern(t_pattern	**pattern)
{
	int	i;

	i = 0;
	if (!pattern)
		return ;
	while (pattern[i])
	{
		if (pattern[i]->name)
			free(pattern[i]->name);
		free(pattern[i++]);
	}
	free(pattern);
}

void    free_pat_mat(t_e_counts *c)
{
    if (c->material)
        free_material(c->material);
    if (c->pat)
        free_pattern(c->pat);
}