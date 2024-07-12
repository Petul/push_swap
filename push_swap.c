/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:58:40 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 10:54:58 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

/* Pushes everything from B to A checking that it goes in the correct place.
 * It the location is not correct A is reverse rotated. As a consequence of B
 * being reverse ordered, reverse rotating A will be shorter than normal
 * rotation of A
 */
static int	push_all_to_a(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;

	while (s->b->len > 0)
	{
		if ((s->b->arr[0] < s->a->arr[0]
				&& s->b->arr[0] > s->a->arr[s->a->len - 1])
			|| ((s->a->arr[0] < s->a->arr[s->a->len - 1])
				&& (s->b->arr[0] > s->a->arr[s->a->len - 1]
					|| s->b->arr[0] < s->a->arr[0])))
			new_cmds = construct_n_cmd(PA, 1);
		else
			new_cmds = construct_n_cmd(RRA, 1);
		if (!new_cmds)
			return (-1);
		stack_exec_cmds(s, *new_cmds);
		ft_lstadd_back(cmd_list, *new_cmds);
		free(new_cmds);
	}
	return (1);
}

static int	sort_three(t_stacks *s, t_list **cmds)
{
	if (!is_ordered(s->a))
	{
		append_cmd_to_cmds(SA, cmds, 1);
		stack_swap(s->a);
	}
	if (rotate_a_min_on_top(s, cmds) < 0)
		return (-1);
	return (1);
}

/*
*	1)	Push 2 elements from A to B
*	2)	Push elements one at a time from A to B so that they are in descending
*		order
*	3)	Rotate B so that largest element is at the top
*	4)	Push all elements to A
*/
static t_list	**turksort(t_stacks *s)
{
	t_list	**cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	if (!is_ordered(s->a))
	{
		if (rev_sort_into_b(s, cmds) < 0)
			return (NULL);
		if (rotate_b_max_on_top(s, cmds) < 0)
			return (NULL);
		if (sort_three(s, cmds) < 0)
			return (NULL);
		if (push_all_to_a(s, cmds) < 0)
			return (NULL);
	}
	if (rotate_a_min_on_top(s, cmds) < 0)
		return (NULL);
	return (cmds);
}

int	push_swap(t_stacks *s)
{
	t_list		**cmds;

	cmds = turksort(s);
	if (!cmds)
		return (-1);
	ft_lstiter(*cmds, &write_cmd);
	ft_lstclear(cmds, &free);
	free(cmds);
	return (0);
}
