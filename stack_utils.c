/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:02:36 by pleander          #+#    #+#             */
/*   Updated: 2024/07/04 14:57:11 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_push_n(t_stack *target, t_stack *source, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_push(target, source);
		i++;
	}
	return ;
}

void	stack_rot_n(t_stack *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_rot(s);
		i++;
	}
	return ;
}

void	stack_rev_rot_n(t_stack *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_rev_rot(s);
		i++;
	}
	return ;
}

void	stack_exec_cmds(t_stacks *s, t_list *cmd_lst)
{
	if (!cmd_lst || !s)
		return ;
	while (cmd_lst)
	{
		if (*(t_cmd *)(cmd_lst->content) == RA)
			stack_rot(s->a);
		else if (*(t_cmd *)(cmd_lst->content) == RRA) stack_rev_rot(s->a); else if (*(t_cmd *)(cmd_lst->content) == RB)
			stack_rot(s->b);
		else if (*(t_cmd *)(cmd_lst->content) == RRB)
			stack_rev_rot(s->b);
		else if (*(t_cmd *)(cmd_lst->content) == RR)
		{
			stack_rot(s->a);
			stack_rot(s->b);
		}
		else if (*(t_cmd *)(cmd_lst->content) == RRR)
		{
			stack_rev_rot(s->a);
			stack_rev_rot(s->b);
		}
		else if (*(t_cmd *)(cmd_lst->content) == PB)
			stack_push(s->b, s->a);
		else if (*(t_cmd *)(cmd_lst->content) == PA)
			stack_push(s->a, s->b);
		else if (*(t_cmd *)(cmd_lst->content) == SA)
			stack_swap(s->a);
		cmd_lst = cmd_lst->next;
	}
	return ;
}
