/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_to_top.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:52:23 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 10:54:09 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

t_list	**rotate_i_to_top(t_stack *s, size_t i, t_cmd rot, t_cmd rev_rot)
{
	t_list	**new_cmds;

	if (i < s->len - i)
		new_cmds = construct_n_cmd(rot, i);
	else
		new_cmds = construct_n_cmd(rev_rot, s->len - i);
	if (!new_cmds)
		return (NULL);
	return (new_cmds);
}

int	rotate_a_min_on_top(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;
	int		min_i;

	min_i = stack_get_min(s->a);
	if (min_i < 0)
		return (-1);
	new_cmds = rotate_i_to_top(s->a, min_i, RA, RRA);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}

int	rotate_b_max_on_top(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;
	int		max_i;

	max_i = stack_get_max(s->b);
	if (max_i < 0)
		return (-1);
	new_cmds = rotate_i_to_top(s->b, max_i, RB, RRB);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}
