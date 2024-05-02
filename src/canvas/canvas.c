#include "canvas.h"

bool	new_canvas(t_canvas *canvas, int width, int height, char *title)
{
	canvas->mlx = mlx_init(width, height, title, true);
	if (!canvas->mlx)
		return (false);
	canvas->width = &canvas->mlx->width;
	canvas->height = &canvas->mlx->height;
	canvas->img = mlx_new_image(canvas->mlx, width, height);
	if (!canvas->img)
		return (false);
	ft_memset(canvas->img->pixels, 255,
		(*canvas->width * *canvas->height) << 2);
	return (true);
}

t_color	read_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t			*pixel;
	double const	inv_255 = 0.00392157;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ((t_color){0, 0, 0});
	pixel = img->pixels + ((y * img->width + x) << 2);
	return (new_color(pixel[0] * inv_255, pixel[1] * inv_255,
			pixel[2] * inv_255));
}
