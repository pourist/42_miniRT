#include "parser.h"

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	printf("r: %f g %f b: %f \n", minirt.world.ambient.r, minirt.world.ambient.g, minirt.world.ambient.b);
	return (0);
}
