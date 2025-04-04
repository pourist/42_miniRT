/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:04:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:04:40 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <math.h>
# include <sys/stat.h>
# include <pthread.h>

# include "libft.h"
# include "tuples.h"

# ifndef MAXFLOAT
#  define MAXFLOAT	3.40282347e+38F
# endif
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif
# ifndef M_PI_4
#  define M_PI_4 0.785398163397448309616
# endif

# define EPSILON	1e-5
# define MAX_SEQUENCER 8
# define MAX_SEQ_VALUES 8
# define THREADS_MAX	64
# define THREADS_FRACTION 0.5
# define INV_255 0.00392156862745098

typedef struct s_sequencer
{
	int		base;
	int		index;
}	t_sequencer;

typedef struct s_thread_data
{
	void	*data;
	int		start;
	int		end;
}	t_thread_data;

typedef struct s_threads_setup
{
	int	nb_iters;
	int	nb_threads;
	int	iters_per_thread;
}	t_threads_setup;

typedef void	*(*t_thread_fn)(void *);

/*
The function eq_dbl is used to compare two double values with a precision of
EPSILON (0.00001). It returns true if the two values are equal, false otherwise.
*/
bool		eq_dbl(double a, double b);
double		ft_max(double a, double b, double c);
double		ft_min(double a, double b, double c);
void		ft_swap(double *a, double *b);
double		ft_atof(char *str);
// sequencer.c
void		new_sequencer(t_sequencer *gen);
double		halton_sequence(t_sequencer *gen);
double		van_der_corput_sequence(t_sequencer *gen);
double		next_sequence(t_sequencer *gen);
double		rand_dbl(void);
// threads.c
bool		set_threads_data(void *data, pthread_t **threads,
				t_thread_data **t_data, t_threads_setup *setup);
bool		exec_threads_for(t_thread_fn thread_fn, pthread_t *threads,
				t_thread_data *thread_data, int *nb_threads);
void		threads_pool(pthread_t **threads, t_thread_data **t_data,
				int *nb_threads);
#endif
