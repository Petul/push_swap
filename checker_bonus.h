/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:44:09 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 13:40:31 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stddef.h>
# include "libft/include/libft.h"

typedef struct s_stack
{
	int		*arr;
	size_t	size;
	size_t	len;

}	t_stack;

typedef struct s_stacks
{
	t_stack	*a;
	t_stack	*b;
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
	RRR,
	ERR
}	t_cmd;

int			checker(t_stacks *s);
t_stacks	*create_stacks(int ac, char **av);
void		delete_stack(t_stack *stack);
int			str_is_digit_and_space(char *str);
t_stack		*create_stack(size_t size, size_t len, int *num_array);
int			*parse_args(int *nums, int ac, char **av);
int			overflowed(char *s, int n);
void		free_array(void **arr);
int			is_unique(int *i_arr, int nums);
void		stack_rot_n(t_stack *stack, size_t n);
void		stack_rev_rot_n(t_stack *stack, size_t n);
void		stack_swap(t_stack *stack);
void		stack_push_n(t_stack *target, t_stack *source, size_t n);
void		stack_exec_cmds(t_stacks *s, t_list *cmd_lst);
int			append_cmd_to_cmds(t_cmd cmd, t_list **cmds, size_t n);


#endif
