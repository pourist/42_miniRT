#include "test.h"

Test(random, random)
{
	printf("over double max: %f\n", ft_atof("1.7976931348623157e+308"));
	printf("over double max: %f\n", ft_atof("1e+309"));
	printf("over double max: %e\n", ft_atof("1.7976931348623157e+308"));
	printf("over double max: %e\n", ft_atof("1e+309"));

	printf("within double max: %f\n", ft_atof("1.23e+100"));
	printf("within double min: %f\n", ft_atof("1.23e-100"));

	// Valores en el borde del rango
	printf("at double max: %e\n", ft_atof("1.7976931348623157e+308"));
	printf("at double min: %e\n", ft_atof("2.2250738585072014e-308"));

	// Valores más allá del rango
	printf("over double max: %e\n", ft_atof("1e+309"));
	printf("under double min: %e\n", ft_atof("1e-324"));

	// Valores negativos
	printf("negative within double max: %f\n", ft_atof("-1.23e+100"));
	printf("negative within double min: %f\n", ft_atof("-1.23e-100"));
	printf("negative at double max: %e\n", ft_atof("-1.7976931348623157e+308"));
	printf("negative over double max: %e\n", ft_atof("-1e+309"));

	// Valores extremadamente grandes y pequeños para probar el infinito
	printf("extremely large: %e\n", ft_atof("1e+500"));
	printf("extremely small: %e\n", ft_atof("1e-500"));
}
