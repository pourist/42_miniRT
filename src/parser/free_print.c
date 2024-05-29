#include "parser.h"

int	print_error(char	*text)
{
	write(1, text, ft_strlen(text));
    write(1, "\n", 1);
	return (1);
}

int	free_print_error(t_world *minirt, char *str)
{
	free_world(minirt);
	return(print_error(str));
}

int	free_s(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (1);
}