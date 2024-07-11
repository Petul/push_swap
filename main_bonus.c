/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:22:32 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 16:47:45 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/ft_printf.h"
#include "checker_bonus.h"

static int	check_args(int ac, char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (!str_is_valid(av[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	error_exit(void)
{
	ft_dprintf(2, "Error\n");
	exit(1);
}

static void	free_stacks(t_stacks *s)
{
	delete_stack(s->a);
	delete_stack(s->b);
	free(s);
}

int	main(int argc, char **argv)
{
	t_stacks	*s;

	if (argc < 2)
		return (0);
	if (!check_args(argc, argv))
		error_exit();
	s = create_stacks(argc - 1, &argv[1]);
	if (!s)
		error_exit();
	if (checker(s) < 0)
	{
		free_stacks(s);
		error_exit();
	}
	free_stacks(s);
	return (0);
}
