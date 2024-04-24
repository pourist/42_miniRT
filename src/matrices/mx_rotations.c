#include "matrices.h"

t_matrix	rotation_x(double rad)
{
	double const	table[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, cos(rad), -sin(rad), 0},
	{0, sin(rad), cos(rad), 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX));
}

t_matrix	rotation_y(double rad)
{
	double const	table[MAX][MAX] = {
	{cos(rad), 0, sin(rad), 0},
	{0, 1, 0, 0},
	{-sin(rad), 0, cos(rad), 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX));
}

t_matrix	rotation_z(double rad)
{
	double const	table[MAX][MAX] = {
	{cos(rad), -sin(rad), 0, 0},
	{sin(rad), cos(rad), 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX));
}
