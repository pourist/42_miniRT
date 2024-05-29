#include "parser.h"

int ft_strarr_len(char **line)
{
    int count;
	
	count = 0;
    while (line[count] != NULL)
    {
        count++;
    }
    return (count);
}

int	is_valid_number(char *str)
{
	int	point;
	int	i;
	char *temp;
	
	temp = str;
	i = 0;
	point = 0;
	if (*temp == '+' || *temp == '-')
		temp++;
	while (*temp)
	{
		if (ft_isdigit(*temp))
			i = 1;
		else if (*temp == '.' && !point && i)
			point = 1;
		else
			return (0);
		temp++;
	}
	return (i);
}

int	str_valid_numbers(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_valid_number(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_inrange(int numb, int min, int max)
{
	if (numb < min || numb > max)
		return (0);
	return (1);
}