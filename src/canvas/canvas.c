#include "canvas.h"

static uint32_t	convert_value(double value)
{
	if (value > 1)
		value = 1;
	value *= 255 + 0.5;
	return (value);
}

int	get_rgba(t_color color)
{
	return (
		convert_value(color.r) << 24
		| convert_value(color.g) << 16
		| convert_value(color.b) << 8
		| convert_value(color.a)
	);
}

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
	ft_memset(canvas->img->pixels, get_rgba(color(0, 0, 0, 1)),
		canvas->img->width * canvas->img->height * sizeof(int32_t));
	return (true);
}

void	write_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	uint8_t		*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = &img->pixels[(y * img->width + x) * sizeof(int32_t)];
	*(pixel++) = convert_value(color.r);
	*(pixel++) = convert_value(color.g);
	*(pixel++) = convert_value(color.b);
	*(pixel) = convert_value(color.a);
}

t_color	read_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t		*pixel;
	uint32_t	c;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ((t_color){0, 0, 0, 0});
	pixel = &img->pixels[(y * img->width + x) * sizeof(int32_t)];
	c = *(pixel++) << 24;
	c |= *(pixel++) << 16;
	c |= *(pixel++) << 8;
	c |= *(pixel);
	return (color((c >> 24) / 255.0, (c >> 16 & 0xFF) / 255.0,
			(c >> 8 & 0xFF) / 255.0, (c & 0xFF) / 255.0));
}
