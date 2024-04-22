#ifndef MATRICES_H
# define MATRICES_H

# include "libft.h"

# define MAX 4
# define SIZE 16

typedef struct s_matrix {
	double	mx[MAX][MAX];
	size_t	size;
}	t_matrix;

t_matrix	new_matrix(const double table[MAX][MAX], size_t size);

#endif
