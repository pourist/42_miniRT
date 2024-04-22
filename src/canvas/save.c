#include "canvas.h"

static void	write_ppm(t_canvas *canvas, int fd)
{
	size_t	i;
	size_t	j;
	uint8_t	*pixel;
	int			rgb[3];

	pixel = canvas->img->pixels;
	i = 0;
	while (i < canvas->img->height)
	{
		j = 0;
		while (j < canvas->img->width)
		{
			rgb[0] = *(pixel++);
			rgb[1] = *(pixel++);
			rgb[2] = *(pixel++);
			++pixel;
			ft_printf_fd(fd, "%d %d %d ", rgb[0], rgb[1], rgb[2]);
			++j;
		}
		write(fd, "\n", 1);
		++i;
	}
	write(fd, "\n", 1);
}

void	canvas_to_ppm(t_canvas *canvas, char *filename)
{
	int			fd;

	if (!canvas || !canvas->img || !canvas->img->pixels)
		return ;
	if (!filename)
		filename = "default.ppm";
	else
		filename = ft_strjoin(filename, ".ppm");
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_TRUNC, 0644);
	ft_printf_fd(fd, "P3\n%d %d\n255\n", canvas->img->width, canvas->img->height);
	write_ppm(canvas, fd);
	close(fd);
}
