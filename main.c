/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:23:18 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 19:39:33 by pleander         ###   ########.fr       */
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
	 // ft_printf("Stack A:\n");
	 // print_stack(s->a);
	 // ft_printf("Stack B:\n");
	 // print_stack(s->b);
	if (!s)
		error_exit();
	if (push_swap(s) < 0)
		error_exit(); //free stuff
	// ft_printf("Stack A:\n");
	// print_stack(s->a);
	// ft_printf("Stack B:\n");
	// print_stack(s->b);
	delete_stacks(s);
	return (0);
}


