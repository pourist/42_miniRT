#ifndef PARSER_H
#define PARSER_H

#include "camera.h"
#include "canvas.h"
#include "lights.h"
#include "parser_error.h"
#include "world.h"
#include "obj_loader.h"
#include <limits.h>

#define WIDTH 1920
#define HEIGHT 1080

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_e_counts {
  int a_light;
  int camera;
  int light;
  int sphere;
  int plane;
  int cylinder;
  int unknown;
  int fd;
  int cone;
  int cube;
  int mat;
  int ob;
  t_material **material;
} t_e_counts;

typedef struct s_line_parse_env {
  char *temp;
  char **line;
  int line_number;
  int error_type;
  int type;
  int l;
  int o;
  t_material **material;
} t_line_parse_env;

typedef struct s_cylinder_info {
  double diam;
  double height;
  double r;
  double g;
  double b;

} t_cylinder_info;

typedef struct s_cone_info {
  double diam;
  double height;
  double r;
  double g;
  double b;
  bool open;
} t_cone_info;

typedef enum e_element_type {
  AMBIENT,
  CAMERA,
  LIGHT,
  SPHERE,
  CYLINDER,
  PLANE,
  CONE,
  CUBE,
  MATERIAL,
  EMPTY_LINE,
  OBJ,
} t_element_type;

typedef struct s_ext_obj
{
    char    **center;
    char    **axis;
    char    **scale;
} t_e_obj;


typedef struct s_cube_info {
  double width;
  double height;
  double depth;
  double r;
  double g;
  double b;
} t_cube_info;

// free_print
int print_error(char *text);
int free_print_error(t_world *minirt, char *str);
int free_s(char **s);
void free_mini_rt(t_mini_rt *mini_rt);
// parser_utils
int is_valid_number(char *str);
int is_in_range(double numb, double min, double max);
int str_valid_numbers(char **str);
int ft_strarr_len(char **line);
int are_in_range(char **arr, double min, double max);
// parser
int parser(int argc, char **argv, t_mini_rt *minirt);
void flush_fd(int fd);
// init_mini_re
int init_minirt(t_mini_rt *minirt, t_e_counts *count);
// init_ambient
int init_ambient(t_line_parse_env *env, t_world *world);
void make_ambient(char **rgb, double ratio, t_world *minirt);
// element_counter
int init_counter_fd(t_e_counts *count, char *file);
// error
int file_error(t_line_parse_env *parse, char *text);
int file_error_line(int line, char *text);
char *find_error(int type);
// valid args
int solo(char *number, double min, double max, t_line_parse_env *env);
int triplets(char **triple, double min, double max, t_line_parse_env *env);
// line parser
int read_lines_init(t_world *world, t_mini_rt *minirt, t_e_counts *count);
// camera
int init_camera(t_line_parse_env *env, t_camera *camera);
// light
int init_light(t_line_parse_env *env, t_light *light);
// sphere
int init_sphere(t_line_parse_env *env, t_shape *obj);
// plane
int init_plane(t_line_parse_env *env, t_shape *obj);
// cylinder
int init_cylinder(t_line_parse_env *env, t_shape *obj);
// cone
int init_cone(t_line_parse_env *env, t_shape *obj);
// cube
int init_cube(t_line_parse_env *env, t_shape *obj);
// obj
int init_obj(t_line_parse_env *env, t_shape *obj, t_world *world);
// calculate_rotation.c
void calculate_rotation_matrix(t_vector *default_normal, t_vector *user_normal,
                               t_matrix *rotation_matrix);
// material_parser
int find_material(t_material **material, t_shape *obj, char *name,
                  t_line_parse_env *env);
int read_material(t_e_counts *count, char *file);
int mat_color(t_material *material, int *index, t_line_parse_env *env);
int mat_ambient(t_material *material, int *index, t_line_parse_env *env);
int mat_diffuse(t_material *material, int *index, t_line_parse_env *env);
int mat_specular(t_material *material, int *index, t_line_parse_env *env);
int mat_shininess(t_material *material, int *index, t_line_parse_env *env);
int mat_reflect(t_material *material, int *index, t_line_parse_env *env);
int mat_trans(t_material *material, int *index, t_line_parse_env *env);
int mat_refractive(t_material *material, int *index, t_line_parse_env *env);
void free_material(t_material **material);
int mat_tex(t_material *material, int *index, t_line_parse_env	*env);
#endif
