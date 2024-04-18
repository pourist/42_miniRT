/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:47:17 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/04/19 00:10:05 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

# include <stdlib.h>

/*  
* @breif t_tuple is a struct that represents a point or a vector in 3D space
*	@param x : x-axis coordinate
*	@param y : y-axis coordinate
*	@param z : z-axis coordinate
*	@param w : Distinguish between point and vector. 1 for point, 0 for vector
*/
typedef struct s_tuple {
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

/*  
*	@brief the type t_point is an alias for t_tuple who has w = 1
*/
typedef t_tuple	t_point;
/*  
* @brief the type t_vector is an alias for t_tuple who has w = 0
*/
typedef t_tuple	t_vector;


t_tuple	tuple(double x, double y, double z, double w);

t_tuple	point(double x, double y, double z);

t_tuple vector(double x, double y, double z);

#endif
