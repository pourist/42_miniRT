/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:50 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:15:51 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

t_checker	uv_checkers(double width, double height, t_pattern *a,
				t_pattern *b)
{
	return ((t_checker){width, height, a, b});
}

void	texture_map(t_pattern *pattern, t_checker *checkers,
		t_uv_mapping uv_mapping_fn)
{
	pattern->texture_map.uv_pattern = *checkers;
	pattern->texture_map.uv_mapping_fn = uv_mapping_fn;
}
