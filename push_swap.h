/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:43:42 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 19:28:24 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include <stddef.h>
# include "libft/include/libft.h"

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

enum e_cmd
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

int			push_swap(t_stacks *s);
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
void		stack_rev_rot_n(t_stack *s, size_t n);
void		stack_rot_n(t_stack *s, size_t n);
void		stack_push_n(t_stack *target, t_stack *source, size_t n);
void		do_nothing(void *p);
t_list		**construct_insertion_cmd(size_t *top_dsts);
void		stack_exec_cmds(t_stacks *s, t_list *cmd_lst);
int			rev_sort_into_b(t_stacks *s, t_list **cmd_list);
void		ft_puts(void *str);
t_list		**construct_n_cmd(char *cmd, size_t n);
size_t	get_min_index(size_t *arr, size_t len);



#endif

