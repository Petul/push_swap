/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:20:26 by pleander          #+#    #+#             */
/*   Updated: 2024/06/26 10:30:17 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "push_swap.h"

static t_stack	*create_stack_a(int ac, char **av)
{
	int		n_nums;
	int		*num_array;
	t_stack	*stack_a;

	num_array = parse_args(&n_nums, ac, av);
	if (!num_array)
		return (NULL);
	stack_a = create_stack(n_nums, n_nums, num_array);
	if (!stack_a)
		return (NULL);
	return (stack_a);
}

static t_stack	*create_stack_b(int n_nums)
{
	int		*num_array;
	t_stack	*stack_b;

	num_array = ft_calloc(n_nums, sizeof(int));
	if (!num_array)
		return (NULL);
	stack_b = create_stack(n_nums, 0, num_array);
	if (!stack_b)
		return (NULL);
	return (stack_b);
}

t_stacks	*create_stacks(int ac, char **av)
{
	t_stacks	*s;

	s = ft_calloc(1, sizeof(t_stacks));
	if (!s)
		return (NULL);
	s->a = create_stack_a(ac, av);
	if (!s->a)
	{
		free(s);
		return (NULL);
	}
	s->b = create_stack_b(s->a->len);
	if (!s->b)
	{
		free(s);
		delete_stack(s->a);
		return (NULL);
	}
	return (s);
}
