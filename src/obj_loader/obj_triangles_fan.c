/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_triangles_fan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:10:55 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:10:58 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_loader.h"

static void	set_normals(t_obj_loader *loader, int *indices, int *i,
		t_vector n[3])
{
	if (indices[0] < loader->n_max && indices[*i] < loader->n_max
		&& indices[*i + 1] < loader->n_max)
	{
		n[0] = loader->normals[indices[0]];
		n[1] = loader->normals[indices[*i]];
		n[2] = loader->normals[indices[*i + 1]];
	}
}

static void	set_vertices(t_obj_loader *loader, int *indices, int *i,
		t_point v[3])
{
	if (indices[0] < loader->v_max && indices[*i] < loader->v_max
		&& indices[*i + 1] < loader->v_max)
	{
		v[0] = loader->vertices[indices[0]];
		v[1] = loader->vertices[indices[*i]];
		v[2] = loader->vertices[indices[*i + 1]];
	}
}

static void	set_uvs(t_obj_loader *loader, int *indices, int *i, t_uv uv[3])
{
	if (indices[0] < loader->uv_max && indices[*i] < loader->uv_max
		&& indices[*i + 1] < loader->uv_max)
	{
		uv[0] = loader->uvs[indices[0]];
		uv[1] = loader->uvs[indices[*i]];
		uv[2] = loader->uvs[indices[*i + 1]];
		loader->triangles[loader->t_count].material.pattern.v1_uv = uv[0];
		loader->triangles[loader->t_count].material.pattern.v2_uv = uv[1];
		loader->triangles[loader->t_count].material.pattern.v3_uv = uv[2];
	}
}

static void	create_triangle(t_obj_loader *loader, int *indices[3], int *i)
{
	t_point		v[3];
	t_vector	n[3];
	t_uv		uv[3];

	if (indices[0][0] >= 0 && indices[0][*i] >= 0 && indices[0][*i + 1] >= 0)
	{
		set_vertices(loader, indices[0], i, v);
		if (indices[2][0] >= 0 && indices[2][*i] >= 0
			&& indices[2][*i + 1] >= 0)
		{
			set_normals(loader, indices[2], i, n);
			new_smooth_triangle(v, n, &loader->triangles[loader->t_count]);
		}
		else
			new_triangle(&v[0], &v[1], &v[2],
				&loader->triangles[loader->t_count]);
		if (loader->current_mtllib && loader->current_mtllib->current_mtl)
			loader->triangles[loader->t_count].material = *loader
				->current_mtllib->current_mtl;
		if (indices[1][0] >= 0 && indices[1][*i] >= 0
			&& indices[1][*i + 1] >= 0)
			set_uvs(loader, indices[1], i, uv);
	}
}

bool	fan_triangulation(t_obj_loader *loader, int *indices[3], int *p_len)
{
	int			i;

	i = 0;
	while (++i < *p_len - 1)
	{
		if (loader->t_count >= loader->t_max)
			return (false);
		create_triangle(loader, indices, &i);
		add_child(loader->current_gp, &loader->triangles[loader->t_count]);
		loader->t_count++;
	}
	return (true);
}
