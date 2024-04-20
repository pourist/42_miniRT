#include "tuples.h"
#include <stdio.h>

typedef struct s_projectile {
	t_point		position;
	t_vector	velocity;
}	t_projectile;

typedef struct s_environment {
	t_vector	gravity;
	t_vector	wind;
}	t_environment;

t_projectile	tick(t_environment env, t_projectile proj)
{
	t_point		pos;
	t_vector	vel;

	pos = add(proj.position, proj.velocity);
	vel = add(proj.velocity, env.gravity);
	vel = add(vel, env.wind);
	return ((t_projectile){pos, vel});
}

int	main(void)
{
	t_projectile	p;
	t_environment	e;

	p.position = point(0, 1, 0);
	p.velocity = normalize(vector(1, 1, 0));
	e.gravity = vector(0, -0.1, 0);
	e.wind = vector(-0.01, 0, 0);
	while (p.position.y > 0.0)
	{
		printf("(%f, %f, %f)\n", p.position.x, p.position.y, p.position.z);
		p = tick(e, p);
	}
	printf("Final position >> (%f, %f, %f)\n", p.position.x, p.position.y, p.position.z);
	return (0);
}
