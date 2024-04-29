#include "canvas.h"

static uint8_t	convert_value(double value)
{
	if (value > 1.0)
		return (255);
	else if (value < 0.0)
		return (0);
	else
		return (value * 255.0 + 0.5);
}

uint32_t	get_rgb(t_color color)
{
	return (convert_value(color.b) << 16 | convert_value(color.g) << 8
		| convert_value(color.r) | 0xFF000000);
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
	ft_memset(canvas->img->pixels, 255,
		(*canvas->width * *canvas->height) << 2);
	return (true);
}

void	write_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	uint8_t		*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = &img->pixels[((y * img->width) + x) << 2];
	*(pixel) = convert_value(color.r);
	*(++pixel) = convert_value(color.g);
	*(++pixel) = convert_value(color.b);
}

void	write_pixel_32(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t		*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = &img->pixels[((y * img->width) + x) << 2];
	*(uint32_t *)pixel = color;
}

/* t_color	read_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t		*pixel;
	uint32_t	c;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ((t_color){0, 0, 0, 0});
	pixel = &img->pixels[(y * img->width + x) << 2];
	c = *(pixel++) << 24;
	c |= *(pixel++) << 16;
	c |= *(pixel++) << 8;
	c |= *(pixel);
	return (new_color((c >> 24) / 255, (c >> 16 & 0xFF) / 255,
			(c >> 8 & 0xFF) / 255, (c & 0xFF) / 255));
} */

/* This read_pixel implementation casting the pixels to uint32_t*,
 * to find directly the whole pixel, than extract the rgba value
 * and divide by 255 to obtain a value between 0 and 1, actually
 * to improve a little bit the performance instant of division 
 * multiplication is used with the inverse value of 255 (1/255). */
t_color	read_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint32_t		pixel;
	double const	inv_255 = 0.00392157;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ((t_color){0, 0, 0});
	pixel = ((uint32_t *)img->pixels)[y * img->width + x];
	return (new_color((pixel & 0xFF) * inv_255, (pixel >> 8 & 0xFF) * inv_255,
			(pixel >> 16 & 0xFF) * inv_255));
}
