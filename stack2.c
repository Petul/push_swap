/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:27:46 by pleander          #+#    #+#             */
/*   Updated: 2024/07/10 16:42:52 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* Rotates the stack.
* The first element becomes the last
*/
void	stack_rot_n(t_stack *stack, size_t n)
{
	size_t	i;
	int		first;

	i = 0;
	while (i < n)
	{
		if (stack->len < 2)
			return ;
		first = stack->arr[0];
		ft_memmove(stack->arr, stack->arr + 1, (stack->len - 1) * sizeof(int));
		stack->arr[stack->len - 1] = first;
		i++;
	}
}

/*
* Reverse rotates the stack.
* The last element becomes the first
*/
void	stack_rev_rot_n(t_stack *stack, size_t n)
{
	size_t	i;
	int		last;

	i = 0;
	while (i < n)
	{
		if (stack->len < 2)
			return ;
		last = stack->arr[stack->len - 1];
		ft_memmove(stack->arr + 1, stack->arr, (stack->len - 1) * sizeof(int));
		stack->arr[0] = last;
		i++;
	}
}

/*
* Gets the index of the max value in a stack
*/
int	stack_get_max(t_stack *s)
{
	int		max_i;
	int		max_n;
	size_t	i;

	if (s->len < 1)
		return (0);
	max_i = 0;
	max_n = s->arr[0];
	i = 0;
	while (i < s->len)
	{
		if (s->arr[i] > max_n)
		{
			max_i = i;
			max_n = s->arr[i];
		}
		i++;
	}
	return (max_i);
}

/*
* Gets the index of the min value in a stack
*/
int	stack_get_min(t_stack *s)
{
	int		min_i;
	int		min_n;
	size_t	i;

	if (s->len < 1)
		return (0);
	min_i = 0;
	min_n = s->arr[0];
	i = 0;
	while (i < s->len)
	{
		if (s->arr[i] < min_n)
		{
			min_i = i;
			min_n = s->arr[i];
		}
		i++;
	}
	return (min_i);
}
