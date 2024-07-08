/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:42:06 by pleander          #+#    #+#             */
/*   Updated: 2024/07/08 11:37:29 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/ft_printf.h"
#include "libft/include/libft.h"
#include "push_swap.h"

/* Takes list of numbers separated by space and returns a stack */
t_stack	*create_stack(size_t size, size_t len, int *num_array)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->arr = num_array;
	stack->len = len;
	stack->size = size;
	return (stack);
}

/* Deletes and frees the stack */
void delete_stack(t_stack *stack)
{
	free(stack->arr);
	free(stack);
	return ;
}

void print_stack(t_stack *stack)
{
	int i;

	i = 0;
	while (i < (int)stack->size)
	{
		if (i < (int)stack->len)
			ft_printf("%d: %d\n", i, stack->arr[i]);
		else
			ft_printf("%d: -\n", i);
		i++;
	}
	ft_printf("\n");
}

/* 
* Swaps first to elements at top of the stack.
* Do nothing if there is one or less elements 
*/
void stack_swap(t_stack *stack)
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
void stack_push(t_stack *target, t_stack *source)
{
	if (source->len < 1)
		return ;
	ft_memmove(target->arr + 1, target->arr, target->len * sizeof(int));
	target->len++;
	target->arr[0] = source->arr[0];
	source->len--;
	ft_memmove(source->arr, source->arr + 1, source->len * sizeof(int));
	return ;
}
