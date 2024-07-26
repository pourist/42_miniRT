/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:06:49 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:06:50 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

bool	new_canvas(t_canvas *canvas, int width, int height, char *title)
{
	canvas->mlx = mlx_init(width, height, title, true);
	if (!canvas->mlx)
		return (false);
	canvas->img = mlx_new_image(canvas->mlx, width, height);
	if (!canvas->img)
		return (false);
	ft_memset(canvas->img->pixels, 255,
		(canvas->img->width * canvas->img->height) << 2);
	return (true);
}

t_color	*read_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color *color)
{
	uint8_t			*pixel;
	double const	inv_255 = 0.00392157;

	if ((x >= img->width || y >= img->height) || !img || !img->pixels)
		return (NULL);
	pixel = img->pixels + ((y * img->width + x) << 2);
	color->r = pixel[0] * inv_255;
	color->g = pixel[1] * inv_255;
	color->b = pixel[2] * inv_255;
	return (color);
}

t_color	*pixel_at(mlx_texture_t *texture, uint32_t x, uint32_t y,
			t_color *color)
{
	uint8_t			*pixel;
	double const	inv_255 = 0.00392157;

	if ((x >= texture->width || y >= texture->height) || !texture
		|| !texture->pixels)
		return (NULL);
	pixel = texture->pixels + ((y * texture->width + x)
			* texture->bytes_per_pixel);
	color->r = pixel[0] * inv_255;
	color->g = pixel[1] * inv_255;
	color->b = pixel[2] * inv_255;
	return (color);
}

t_color	*full_pixel_at(mlx_texture_t *texture, uint32_t x, uint32_t y,
			t_color *color)
{
	uint8_t			*pixel;

	if ((x >= texture->width || y >= texture->height) || !texture
		|| !texture->pixels)
		return (NULL);
	pixel = texture->pixels + ((y * texture->width + x)
			* texture->bytes_per_pixel);
	color->r = pixel[0];
	color->g = pixel[1];
	color->b = pixel[2];
	return (color);
}
