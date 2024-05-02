#include "camera.h"

t_matrix	view_transform(t_point *from, t_point *to, t_vector *up)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation_transform;

	forward = normalize(subtract(*to, *from));
	left = cross(forward, normalize(*up));
	true_up = cross(left, forward);
	orientation_transform = new_matrix((double [MAX][MAX]){
		{left.x, left.y, left.z, 0},
		{true_up.x, true_up.y, true_up.z, 0},
		{-forward.x, -forward.y, -forward.z, 0},
		{0, 0, 0, 1}
		}, 4);
	return (multiply_matrices(orientation_transform,
			translation(-from->x, -from->y, -from->z)));
}
