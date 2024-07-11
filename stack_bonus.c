/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:42:06 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 13:41:48 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "push_swap.h"

/* Takes list of numbers separated by space and returns a stack */
t_stack	*create_stack(size_t size, size_t len, int *num_array)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->arr = num_array;
	stack->len = len;
	stack->size = size;
	return (stack);
}

/* Deletes and frees the stack */
void	delete_stack(t_stack *stack)
{
	free(stack->arr);
	free(stack);
	return ;
}

/* 
* Swaps first to elements at top of the stack.
* Do nothing if there is one or less elements 
*/
void	stack_swap(t_stack *stack)
{
	int	temp;

	if (stack->len < 2)
		return ;
	temp = stack->arr[0];
	stack->arr[0] = stack->arr[1];
	stack->arr[1] = temp;
	return ;
}

/*
* Pushes item from top of stack source to stack target.
* Does nothing if source stack is empty
*/
void	stack_push_n(t_stack *target, t_stack *source, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (source->len < 1)
			return ;
		ft_memmove(target->arr + 1, target->arr, target->len * sizeof(int));
		target->len++;
		target->arr[0] = source->arr[0];
		source->len--;
		ft_memmove(source->arr, source->arr + 1, source->len * sizeof(int));
		i++;
	}
}

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
