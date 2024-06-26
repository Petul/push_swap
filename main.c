/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:23:18 by pleander          #+#    #+#             */
/*   Updated: 2024/06/26 10:31:19 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/ft_printf.h"
#include "push_swap.h"


static	int check_args(int ac, char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (!str_is_digit_and_space(av[i]))
			return (0);
		i++;
	}
	return (1);
}

static void error_exit(void)
{
	ft_printf("Error\n");
	exit(1);
}

int main(int argc, char **argv)
{
	t_stacks *s;

	if (argc < 2 || !check_args(argc, argv))
		error_exit();
	s = create_stacks(argc - 1, &argv[1]);
	if (!s)
		error_exit();
	delete_stacks(s);
	return (0);
}


