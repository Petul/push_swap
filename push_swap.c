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
#include "push_swap.h"

static t_stack* create_stack(int ac, char **av)
{
	int	*i_arr;
	int	nums;
	t_stack *stack;

	i_arr = parse_args(&nums, ac, av);
	if (nums < 0)
		return (NULL);
	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->arr = i_arr;
	stack->len = nums;
	stack->start = 0;
	return (stack);
}

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
	t_stack *stack;

	if (argc < 2 || !check_args(argc, argv))
		error_exit();
	stack = create_stack(argc - 1, &argv[1]);
	if (!stack)
		error_exit();
	int i = 0;
	while (i < (int)stack->len)
	{
		ft_printf("%d ", stack->arr[i]);
		i++;
	}
	return (1);
}


