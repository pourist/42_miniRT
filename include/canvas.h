#ifndef CANVAS_H
# define CANVAS_H

# include <stdbool.h>
# include <fcntl.h>
# include "MLX42/MLX42.h"
# include "libft.h"
# include "tuples.h"

# define CANVAS_WIDTH	800
# define CANVAS_HEIGHT 600

typedef struct s_canvas {
	mlx_t				*mlx;
	mlx_image_t			*img;
	int					*width;
	int					*height;
}	t_canvas;

bool		new_canvas(t_canvas *canvas, int width, int height, char *title);
uint32_t	get_rgba(t_color color);
void		write_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
t_color		read_pixel(mlx_image_t *img, uint32_t x, uint32_t y);

void		canvas_to_ppm(t_canvas *canvas, char *filename);

void		handle_keyhook(mlx_key_data_t keydata, void *param);
void		quit(void *param);
#endif
