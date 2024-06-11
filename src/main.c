#include "parser.h"

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	printf("Ambient:     r: %f g: %f b: %f \n", minirt.world.ambient.r, minirt.world.ambient.g, minirt.world.ambient.b);
	printf("Light rgb:   r: %f g: %f b: %f \n", minirt.world.lights[0].intensity.r, minirt.world.lights[0].intensity.g, minirt.world.lights[0].intensity.b);
	printf("Light pos:   x: %f y: %f z: %f \n", minirt.world.lights[0].position.x, minirt.world.lights[0].position.y, minirt.world.lights[0].position.z);
	return (0);
}
