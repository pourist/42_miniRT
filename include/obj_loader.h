/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:01:57 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/26 17:07:57 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include <fcntl.h>

# include "shapes.h"
# include "groups.h"

# define OBJ_PATH "./assets/obj_files/"
# define MTL_PATH "./assets/mtl_files/"
# define TEXTURE_PATH "./assets/textures/"

typedef enum e_obj_type
{
	VERTICE,
	NORMAL,
	FACE,
}	t_obj_type;

typedef struct s_mtl_loader
{
	char			*filename;
	char			**lines;
	char			***tokens;
	int				ignored_lines;
	t_material		*materials;
	t_material		*current_mtl;
	int				m_count;
	int				m_max;
	pthread_mutex_t	m_mutex;
	pthread_mutex_t	ig_lines_mutex;
}	t_mtl_loader;

typedef struct s_obj_group
{
	char const	*name;
	t_shape		group;
}	t_obj_group;

typedef struct s_obj_mtl
{
	char const	*name;
	t_material	material;
}	t_obj_mtl;

typedef struct s_obj_loader
{
	char			*filename;
	char			**lines;
	char			***tokens;
	int				ignored_lines;
	t_mtl_loader	*mtl_loader;
	t_mtl_loader	*current_mtllib;
	int				mtl_count;
	int				mtl_max;
	t_point			*vertices;
	int				v_count;
	int				v_max;
	t_vector		*normals;
	int				n_count;
	int				n_max;
	t_uv			*uvs;
	int				uv_count;
	int				uv_max;
	t_shape			*triangles;
	int				t_count;
	int				t_max;
	t_shape			*groups;
	int				gp_count;
	int				gp_max;
	t_shape			*current_gp;
	t_shape			*default_group;
	pthread_mutex_t	mtl_mutex;
	pthread_mutex_t	v_mutex;
	pthread_mutex_t	n_mutex;
	pthread_mutex_t	uv_mutex;
	pthread_mutex_t	t_mutex;
	pthread_mutex_t	gp_mutex;
	pthread_mutex_t	ig_lines_mutex;
}	t_obj_loader;

// obj_loader.c
t_obj_loader	*new_obj_loader(t_obj_loader *loader, t_shape *group);
// obj_open_read.c
bool			open_file(char const *filename, int *fd, ssize_t *file_size,
					bool is_obj);
bool			read_file_to_memory(char *filename, char **file_content,
					bool is_obj);
bool			check_extension(char const *filename, char const *ext);
// obj_split_file_content.c
bool			split_file_in_lines(char **file_content, char ***lines,
					char ****tokens, int *nb_lines);
void			*split_lines_in_tokens(void *data);
// obj_file_parse_lines.c
bool			obj_parse_line(t_obj_loader *loader, char **params,
					int line_nb);
// obj_file_parser.c
bool			parse_obj_file(t_obj_loader *loader, char const *filename);
// obj_loader_utils.c
bool			print_ignore_message(char const *filename, int *line_nb);
int				ft_matrix_len(char **matrix);
bool			is_float(char *str);
bool			are_floats(char *str1, char *str2, char *str3);
// obj_triangles_parser.c
bool			parse_triangle(t_obj_loader *loader, char **params,
					int *line_nb);
// obj_triangles_fan.c
bool			fan_triangulation(t_obj_loader *loader, int *indices[3],
					int *p_len);
// set_max_values.c
void			*set_max_values(void *data);
// mtl_file_parser.c
bool			load_mtl_files(t_obj_loader *loader, int *nb_iters);
// mtl_lines_parser.c
bool			mtl_parse_line(t_mtl_loader *loader, char **params,
					int line_nb);
// mtl_parse_elements.c
bool			parse_newmtl(t_mtl_loader *loader);
bool			parse_ambient(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_diffuse(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_specular(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_shininess(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_transparency(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_refractive_i(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_diffuse_texture(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_specular_texture(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_shininess_texture(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_transparency_texture(t_mtl_loader *loader,
					t_material *mtl, char **params, int *line_nb);
bool			parse_bump_texture(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_reflection_texture(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_ambient_texture(t_mtl_loader *loader, t_material *mtl,
					char **params, int *line_nb);
bool			parse_displacement_texture(t_mtl_loader *loader,
					t_material *mtl, char **params, int *line_nb);
// obj_parse_elements.c
bool			parse_usemtl(t_obj_loader *loader);
bool			parse_mtllib(t_obj_loader *loader);
//	loader_frees.c
void			free_matrix(char ***matrix);
void			free_3d_array(char ****array);
void			free_loader(t_obj_loader *loader);
void			free_loader_last(t_obj_loader *loader);
void			free_mtl_loader(t_obj_loader *loader, bool free_all);
void			free_mtl_loader_textures(t_obj_loader *loader);
void			destroy_mutex(t_obj_loader *loader);

#endif
