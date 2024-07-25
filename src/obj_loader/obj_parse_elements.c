/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:10:43 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:10:45 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_loader.h"

bool	parse_usemtl(t_obj_loader *loader)
{
	if (loader->current_mtllib
		&& loader->current_mtllib->m_count < loader->current_mtllib->m_max)
	{
		loader->current_mtllib->current_mtl = &loader->current_mtllib
			->materials[loader->current_mtllib->m_count++];
		return (true);
	}
	if (!loader->current_mtllib || (loader->current_mtllib
			&& loader->current_mtllib->m_max == 0))
		return (true);
	return (false);
}

bool	parse_mtllib(t_obj_loader *loader)
{
	if (loader->mtl_count < loader->mtl_max)
	{
		loader->current_mtllib = &loader
			->mtl_loader[loader->mtl_count++];
		return (true);
	}
	return (false);
}
