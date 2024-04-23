#ifndef MATRICES_H
# define MATRICES_H

# include "libft.h"
# include "tuples.h"

# define MAX 4
# define SIZE 16

typedef struct s_matrix {
	double	mx[MAX][MAX];
	int		size;
}	t_matrix;

/* mx.c */
t_matrix	new_matrix(const double table[MAX][MAX], size_t size);
bool		is_eq_mx(t_matrix m1, t_matrix m2);
/* matrix operations 	*/
t_matrix	multiply_matrices(t_matrix m1, t_matrix m2);
t_tuple		multiply_matrix_by_tuple(t_matrix m, t_tuple t);
t_matrix	transpose_matrix(t_matrix m);
/*  matrix attributes */
double		get_determinant(t_matrix m);
t_matrix	get_submatrix(t_matrix m, int del_row, int del_col);

#endif
