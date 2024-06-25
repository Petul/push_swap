/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:23:18 by pleander          #+#    #+#             */
/*   Updated: 2024/06/25 11:58:56 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/ft_printf.h"
#include "libft/include/libft.h"
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

static t_stack	*create_stack_a(int ac, char **av)
{
	int		n_nums;
	int		*num_array;
	t_stack *stack_a;

	num_array = parse_args(&n_nums, ac, av);
	if (n_nums < 0)
		return (NULL);
	stack_a = create_stack(n_nums, n_nums, num_array);
	if (!stack_a)
		return (NULL);
	return (stack_a);
}

static t_stack *crete_stack_b(int n_nums)
{
	int		*num_array;
	t_stack *stack_b;

	num_array = ft_calloc(n_nums, sizeof(int));
	if (!num_array)
		return (NULL);
	stack_b = create_stack(n_nums, 0, num_array);
	if (!stack_b)
		return (NULL);
	return (stack_b);
}

int main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;

	if (argc < 2 || !check_args(argc, argv))
		error_exit();
	stack_a = create_stack_a(argc - 1, &argv[1]);
	if (!stack_a)
		error_exit();
	stack_b = crete_stack_b(stack_a->len);
	return (0);
}


