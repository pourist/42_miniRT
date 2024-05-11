#include "tuples.h"

t_tuple	add(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){
		t1.x + t2.x,
		t1.y + t2.y,
		t1.z + t2.z,
		t1.w + t2.w,
	});
}

t_tuple	subtract(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){
		t1.x - t2.x,
		t1.y - t2.y,
		t1.z - t2.z,
		t1.w - t2.w,
	});
}

t_tuple	negate(t_tuple t)
{
	return ((t_tuple){
		t.x * -1,
		t.y * -1,
		t.z * -1,
		t.w * -1,
	});
}

t_tuple	multiply(t_tuple t, double scalar)
{
	if (scalar == 0)
		return ((t_tuple){0, 0, 0, 0});
	else if (scalar == 1)
		return (t);
	return ((t_tuple){
		t.x * scalar,
		t.y * scalar,
		t.z * scalar,
		t.w * scalar,
	});
}

t_tuple	divide(t_tuple t, double scalar)
{
	double	inverse_scalar;

	inverse_scalar = 1.0 / scalar;
	return ((t_tuple){
		t.x * inverse_scalar,
		t.y * inverse_scalar,
		t.z * inverse_scalar,
		t.w * inverse_scalar,
	});
}
