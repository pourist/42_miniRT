/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:37:47 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/02 17:37:49 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotation_matrix(t_vector *r_axis, double *cos_theta,
			double *sin_theta, t_matrix *r_m)
{
	double		cos_t_inv;

	cos_t_inv = 1 - *cos_theta;
	r_m->mx[0][0] = *cos_theta + r_axis->x * r_axis->x * cos_t_inv;
	r_m->mx[0][1] = r_axis->x * r_axis->y * cos_t_inv - r_axis->z * *sin_theta;
	r_m->mx[0][2] = r_axis->x * r_axis->z * cos_t_inv + r_axis->y * *sin_theta;
	r_m->mx[0][3] = 0;
	r_m->mx[1][0] = r_axis->y * r_axis->x * cos_t_inv + r_axis->z * *sin_theta;
	r_m->mx[1][1] = *cos_theta + r_axis->y * r_axis->y * cos_t_inv;
	r_m->mx[1][2] = r_axis->y * r_axis->z * cos_t_inv - r_axis->x * *sin_theta;
	r_m->mx[1][3] = 0;
	r_m->mx[2][0] = r_axis->z * r_axis->x * cos_t_inv - r_axis->y * *sin_theta;
	r_m->mx[2][1] = r_axis->z * r_axis->y * cos_t_inv + r_axis->x * *sin_theta;
	r_m->mx[2][2] = *cos_theta + r_axis->z * r_axis->z * cos_t_inv;
	r_m->mx[2][3] = 0;
	r_m->mx[3][0] = 0;
	r_m->mx[3][1] = 0;
	r_m->mx[3][2] = 0;
	r_m->mx[3][3] = 1;
}

void	calculate_rotation_matrix(t_vector *default_normal,
			t_vector *user_normal, t_matrix *rotation_matrix)
{
	double		dot_product;
	double		cos_theta;
	double		angle;
	t_vector	rotation_axis;
	double		sin_theta;

	dot_product = dot(default_normal, user_normal);
	cos_theta = dot_product / (sqrt(magnitude_squared(default_normal))
			* sqrt(magnitude_squared(user_normal)));
	angle = acos(cos_theta);
	sin_theta = sin(angle);
	cross(default_normal, user_normal, &rotation_axis);
	normalize(&rotation_axis, &rotation_axis);
	set_rotation_matrix(&rotation_axis, &cos_theta, &sin_theta,
		rotation_matrix);
}
