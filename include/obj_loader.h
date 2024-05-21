#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include <fcntl.h>

# include "shapes.h"
# include "groups.h"

typedef enum e_obj_type
{
	VERTICE,
	NORMAL,
	FACE,
}	t_obj_type;

typedef struct s_obj_loader
{
	int			ignored_lines;
	t_point		*vertices;
	int			vertices_count;
	int			vertices_max;
	t_vector	*normals;
	int			normals_count;
	int			normals_max;
	t_shape		*triangles;
	int			tri_count;
	int			tri_max;
	t_shape		default_group;
	t_shape		*groups;
	int			g_count;
	int			g_max;
	t_shape		*current_g;
}	t_obj_loader;

t_obj_loader	new_obj_loader(void);
bool			parse_obj_file(t_obj_loader *loader, char *filename);
bool			obj_to_group(t_shape *g, t_obj_loader *loader);

#endif
