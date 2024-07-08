/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:02:36 by pleander          #+#    #+#             */
/*   Updated: 2024/07/04 14:56:57 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
		else if (*(t_cmd *)(cmd_lst->content) == RRA)
			stack_rev_rot(s->a);
		else if (*(t_cmd *)(cmd_lst->content) == RB)
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

int	append_cmd_to_cmds(t_cmd cmd, t_list **cmds)
{
	t_cmd *cmd_ptr;
	t_list *new;

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
	return (0);
}
