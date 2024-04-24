#include "matrices.h"

t_matrix	translation(double x, double y, double z)
{
	double const	table[MAX][MAX] = {
	{1, 0, 0, x},
	{0, 1, 0, y},
	{0, 0, 1, z},
	{0, 0, 0, 1}};

	return (new_matrix(table, MAX));
}

t_matrix	scaling(double x, double y, double z)
{
	double const	table[MAX][MAX] = {
	{x, 0, 0, 0},
	{0, y, 0, 0},
	{0, 0, z, 0},
	{0, 0, 0, 1}};

	return (new_matrix(table, MAX));
}
