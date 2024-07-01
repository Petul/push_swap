/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:02:36 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 14:57:09 by pleander         ###   ########.fr       */
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
		if (!ft_strncmp(cmd_lst->content, "ra", 3))
			stack_rot(s->a);
		else if (!ft_strncmp(cmd_lst->content, "rb", 3))
			stack_rot(s->b);
		else if (!ft_strncmp(cmd_lst->content, "rrb", 4))
			stack_rev_rot(s->b);
		else if (!ft_strncmp(cmd_lst->content, "pb", 3))
			stack_push(s->b, s->a);
		else if (!ft_strncmp(cmd_lst->content, "pa", 3))
			stack_push(s->a, s->b);
		cmd_lst = cmd_lst->next;
	}
	return ;
}
