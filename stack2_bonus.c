/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:36:20 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 13:42:24 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "checker_bonus.h"

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

static void	stack_rot2(t_stack *a, t_stack *b)
{
	stack_rot_n(a, 1);
	stack_rot_n(b, 1);
}

static void	stack_rev_rot2(t_stack *a, t_stack *b)
{
	stack_rev_rot_n(a, 1);
	stack_rev_rot_n(b, 1);
}

void	stack_exec_cmds(t_stacks *s, t_list *cmd_lst)
{
	if (!cmd_lst || !s)
		return ;
	while (cmd_lst)
	{
		if (*(t_cmd *)(cmd_lst->content) == RA)
			stack_rot_n(s->a, 1);
		else if (*(t_cmd *)(cmd_lst->content) == RRA)
			stack_rev_rot_n(s->a, 1);
		else if (*(t_cmd *)(cmd_lst->content) == RB)
			stack_rot_n(s->b, 1);
		else if (*(t_cmd *)(cmd_lst->content) == RRB)
			stack_rev_rot_n(s->b, 1);
		else if (*(t_cmd *)(cmd_lst->content) == RR)
			stack_rot2(s->a, s->b);
		else if (*(t_cmd *)(cmd_lst->content) == RRR)
			stack_rev_rot2(s->a, s->b);
		else if (*(t_cmd *)(cmd_lst->content) == PB)
			stack_push_n(s->b, s->a, 1);
		else if (*(t_cmd *)(cmd_lst->content) == PA)
			stack_push_n(s->a, s->b, 1);
		else if (*(t_cmd *)(cmd_lst->content) == SA)
			stack_swap(s->a);
		cmd_lst = cmd_lst->next;
	}
}

int	append_cmd_to_cmds(t_cmd cmd, t_list **cmds, size_t n)
{
	t_cmd	*cmd_ptr;
	t_list	*new;
	size_t	i;

	i = 0;
	while (i < n)
	{
		cmd_ptr = malloc(sizeof(t_cmd));
		if (!cmd_ptr)
			return (-1);
		*cmd_ptr = cmd;
		new = ft_lstnew(cmd_ptr);
		if (!new)
		{
			free(cmd_ptr);
			return (-1);
		}
		ft_lstadd_back(cmds, new);
		i++;
	}
	return (0);
}
