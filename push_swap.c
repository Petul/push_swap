/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:58:40 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 19:39:17 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "libft/include/ft_printf.h" //
#include "push_swap.h"

static int	rotate_b_max_on_top(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;
	size_t	max_i;
	int		max_n;
	size_t	i;

	max_i = 0;
	max_n = s->b->arr[0];
	i = 1;
	while (i < s->b->len)
	{
		if (s->b->arr[i] > max_n)
		{
			max_i = i;
			max_n = s->b->arr[i];
		}
		i++;
	}
	if (max_i < s->b->len - max_i)
		new_cmds = construct_n_cmd(RB, max_i);
	else
		new_cmds = construct_n_cmd(RRB, s->b->len - max_i);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}

static int	push_all_to_a(t_stacks *s, t_list **cmd_list)
{
	t_list **new_cmds;

	new_cmds = construct_n_cmd(RB, s->b->len);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}

static int	push_two_to_b(t_stacks *s, t_list **cmd_list)
{
	t_list **new_cmds;

	new_cmds = construct_n_cmd(PB, 2);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}
/*
*	1)	Push 2 elements from A to B
*	2)	Push elements one at a time from A to B so that they are in descending
*		order
*	3)	Rotate B so that largest element is at the top
*	4)	Push all elements to A
*/
int	push_swap(t_stacks *s)
{
	t_list	**cmd_list;

	cmd_list = ft_calloc(1, sizeof(t_list *));
	if (!cmd_list)
		return (-1);
	if (push_two_to_b(s, cmd_list) < 0)
	 	return (-1);
	rev_sort_into_b(s, cmd_list);
	rotate_b_max_on_top(s, cmd_list);
	push_all_to_a(s, cmd_list);
	ft_lstiter(*cmd_list, &ft_puts);
	ft_lstclear(cmd_list, &do_nothing);
	free(cmd_list);

	return (1);
}
