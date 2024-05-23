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
	int			v_count;
	int			v_max;
	t_vector	*normals;
	int			n_count;
	int			n_max;
	t_shape		*triangles;
	int			t_count;
	int			t_max;
	t_shape		default_group;
	t_shape		*groups;
	int			g_count;
	int			g_max;
	t_shape		*current_g;
}	t_obj_loader;

// obj_loader.c
t_obj_loader	new_obj_loader(void);
void			free_loader(t_obj_loader *loader);
bool			open_obj_file(char *filename, int *fd);
// obj_file_parser.c
bool			parse_obj_file(t_obj_loader *loader, char *filename);
bool			check_extension(char *filename, char *ext);
// obj_loader_utils.c
bool			print_ignore_message(int line_nb);
int				ft_matrix_len(char **matrix);
bool			is_float(char *str);
bool			are_floats(char *str1, char *str2, char *str3);
void			free_array(char **array);
// obj_faces_parser.c
bool			parse_triangle(t_obj_loader *loader, char **params,
					int *line_nb);
// obj_group_parser.c
bool			parse_group(t_obj_loader *loader, char **params, int *line_nb);
// obj_normal_parser.c
bool			parse_normal(t_obj_loader *loader, char **params, int *line_nb);
// obj_vertice_parser.c
bool			parse_vertice(t_obj_loader *loader, char **params,
					int *line_nb);
// set_max_values.c
bool			set_max_values(t_obj_loader *loader, char *filename);

#endif
