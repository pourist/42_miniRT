/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pat_mat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:24 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/17 11:29:25 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_pat_mat(t_e_counts *c)
{
	if (c->material)
		free_material(c->material);
	if (c->pat)
		free_pattern(c->pat);
}
