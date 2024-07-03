/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:45:19 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/02 17:45:20 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	arg_checker(int argc, char **argv)
{
	char	*format;

	format = ft_strrchr(argv[1], '.');
	if (argc < 2)
		return (print_error(ARG_FEW));
	if (argc > 2)
		return (print_error(ARG_MANY));
	if (format == NULL || ft_strncmp(format, ".rt", 4) != 0)
		return (print_error(FILE_FORMAT));
	return (0);
}

int	parser(int argc, char **argv, t_mini_rt *minirt)
{
	t_e_counts	count;

	if (arg_checker(argc, argv))
		return (1);
	if (init_counter_fd(&count, argv[1]))
		return (1);
	if (read_material(&count, argv[1]))
		return (free_material(count.material), 1);
	if (init_minirt(minirt, &count))
		return (free_mini_rt(minirt), 1);
	return (0);
}
