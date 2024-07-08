/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:43:42 by pleander          #+#    #+#             */
/*   Updated: 2024/07/08 11:39:46 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include <stddef.h>
# include "libft/include/libft.h"

# define RR_DIST(a, b) min(a, b) + (a - min(a,b)) + (b - min(a,b))
# define FIRST_A s->a->arr[0]
# define FIRST_B s->b->arr[0]
# define LAST_A s->a->arr[s->a->len - 1]
# define LAST_B s->b->arr[s->b->len - 1]

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

typedef enum e_cmd
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
}	t_cmd;

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
t_list		**construct_insertion_cmd(size_t *top_dsts);
void		stack_exec_cmds(t_stacks *s, t_list *cmd_lst);
int			rev_sort_into_b(t_stacks *s, t_list **cmd_list);
void		write_cmd(void *content);
t_list		**construct_n_cmd(t_cmd cmd, size_t n);
size_t		get_min_index(size_t *arr, size_t len);
int			is_sorted(t_stack *s);
int			is_ordered(t_stack *s);
t_list		**rotate_i_to_top(t_stack *s, size_t i, t_cmd rot, t_cmd rev_rot);
t_list		**sort_in_place(t_stacks *s, t_list **cmds);
int			append_cmd_to_cmds(t_cmd cmd, t_list **cmds);
int			stack_get_max(t_stack *s);
int			stack_get_min(t_stack *s);

#endif

