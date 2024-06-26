/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:43:42 by pleander          #+#    #+#             */
/*   Updated: 2024/06/26 10:30:45 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include <stddef.h>

typedef struct s_stack
{
	int *arr;
	size_t size;
	size_t len;

}	t_stack;

typedef struct s_stacks
{
	t_stack *a;
	t_stack *b;
}	t_stacks;

int			*parse_args(int *nums, int ac, char **av);
int			str_is_digit_and_space(char *str);
void		free_array(void **arr);
t_stacks	*create_stacks(int ac, char **av);
void		delete_stacks(t_stacks *s);
t_stack		*create_stack(size_t size, size_t len, int *num_array);
void		delete_stack(t_stack *stack);
void		print_stack(t_stack *stack);
void		stack_swap(t_stack *stack);
void		stack_push(t_stack *target, t_stack *source);
void		stack_rot(t_stack *stack);
void		stack_rev_rot(t_stack *stack);

#endif

