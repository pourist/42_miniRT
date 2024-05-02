#ifndef CAMERA_H
# define CAMERA_H

# include "matrices.h"
# include "rays.h"

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	transform;
	t_matrix	inverse;
	t_matrix	transpose;
}	t_camera;

// View transform
t_matrix	view_transform(t_point *from, t_point *to, t_vector *up);

// Camera
t_camera	new_camera(double hsize, double vsize, double fov);
t_ray		ray_for_pixel(t_camera *camera, double px, double py);
void		set_transform_camera(t_camera *camera, t_matrix transform);

#endif
