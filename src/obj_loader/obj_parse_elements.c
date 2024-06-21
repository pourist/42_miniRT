#include "obj_loader.h"

bool	parse_usemtl(t_obj_loader *loader)
{
	if (loader->current_mtllib->m_count < loader->current_mtllib->m_max)
	{
		loader->current_mtllib->current_mtl = &loader->current_mtllib
			->materials[loader->current_mtllib->m_count++];
		return (true);
	}
	return (false);
}

bool	parse_mtllib(t_obj_loader *loader)
{
	if (loader->mtl_count < loader->mtl_max)
	{
		loader->current_mtllib = &loader
			->mtl_loader[loader->mtl_count++];
		return (true);
	}
	return (false);
}
