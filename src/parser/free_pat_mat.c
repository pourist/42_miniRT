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

static void	free_pattern_2(t_pattern *pattern)
{
	if (pattern->has_pattern)
	{
		if (pattern->a)
			free(pattern->a);
		if (pattern->b)
			free(pattern->b);
	}
	if (pattern->texture[0])
		mlx_delete_texture(pattern->texture[0]);
	if (pattern->texture[1])
		mlx_delete_texture(pattern->texture[1]);
	if (pattern->texture[2])
		mlx_delete_texture(pattern->texture[2]);
	if (pattern->texture[3])
		mlx_delete_texture(pattern->texture[3]);
	if (pattern->texture[4])
		mlx_delete_texture(pattern->texture[4]);
	if (pattern->texture[5])
		mlx_delete_texture(pattern->texture[5]);
	if (pattern->texture[6])
		mlx_delete_texture(pattern->texture[6]);
	if (pattern->texture[7])
		mlx_delete_texture(pattern->texture[7]);
}

void	free_pattern(t_pattern	**pattern)
{
	int	i;

	i = 0;
	if (!pattern)
		return ;
	while (pattern[i])
	{
		free_pattern_2(pattern[i]);
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
