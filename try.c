#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXBIT 31

// Secuencia de Halton
double halton(int index, int base) {
	double result = 0.0;
	double f = 1.0 / base;
	while (index > 0) {
			result += f * (index % base);
			index /= base;
			f /= base;
	}
	return result;
}

int main() {
	int num_points = 1000;
	
	// Generar puntos usando la secuencia de Halton
	printf("Secuencia de Halton:\n");
	for (int i = 0; i < num_points; i++) {
			double x = halton(i, 2);
			double y = halton(i, 3);
			double z = halton(i, 5);
			printf("(%f, %f, %f)\n", x, y, z);
	}
	return 0;
}
