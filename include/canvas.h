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
	mlx_image_t	*img;
}	t_canvas;

bool		new_canvas(t_canvas *canvas, int width, int height, char *title);
int			get_rgba(t_color color);
void		write_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color);
t_color	read_pixel(mlx_image_t *img, uint32_t x, uint32_t y);

void	canvas_to_ppm(t_canvas *canvas, char *filename);

#endif
