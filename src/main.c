#include "parser.h"

int	main(int argc, char **argv)
{
	t_world	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	return (0);
}
