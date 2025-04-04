/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:01:35 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:01:39 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "patterns.h"

# define VACUUM 1.0
# define AIR 1.00029
# define WATER 1.333
# define GLASS 1.52
# define DIAMOND 2.417

typedef struct s_material
{
	t_color		color;
	t_color		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	t_pattern	pattern;
	double		reflective;
	double		transparency;
	double		refractive_index;
	char		*name;
}	t_material;

typedef struct s_lighting_params
{
	t_color		effective_color;
	t_vector	light_v;
	t_vector	reflect_v;
	double		light_dot_normal;
	double		reflect_dot_eye;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		color;
	t_color		t_color;
	t_vector	t_normal;
}	t_lighting_params;

t_material	*new_material(t_material *material);

#endif
