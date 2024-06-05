#include "obj_loader.h"

int	main(void)
{
	t_obj_loader	loader;

	loader = new_obj_loader();
	parse_obj_file(&loader, "obj_files/test/TriangleFaces.obj");
	return (0);
}
