/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:58:40 by pleander          #+#    #+#             */
/*   Updated: 2024/07/05 16:13:17 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "push_swap.h"

static int	rotate_b_max_on_top(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;
	size_t	max_i;
	int		max_n;
	size_t	i;

	max_i = 0;
	max_n = FIRST_B;
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
	new_cmds = rotate_i_to_top(s->b, max_i, RB, RRB);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}

/* Pushes everything from B to A checking that it goes in the correct place.
 * It the location is not correct A is reverse rotated. As a consequence of B
 * being reverse ordered, reverse rotating A will be shorter than normal rotation of A
 */
static int	push_all_to_a(t_stacks *s, t_list **cmd_list)
{
	t_list **new_cmds;

	while (s->b->len > 0)
	{
		if ((FIRST_B < FIRST_A && FIRST_B > LAST_A)
			|| ((FIRST_A < LAST_A) && (FIRST_B > LAST_A || FIRST_B < FIRST_A)))
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

static int	rotate_a_min_on_top(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;
	size_t	min_i;
	int		min_n;
	size_t	i;

	min_i = 0;
	min_n = FIRST_A;
	i = 1;
	while (i < s->a->len)
	{
		if (s->a->arr[i] <= min_n)
		{
			min_i = i;
			min_n = s->a->arr[i];
		}
		i++;
	}
	new_cmds = rotate_i_to_top(s->a, min_i, RA, RRA);
	if (!new_cmds)
		return (-1);
	stack_exec_cmds(s, *new_cmds);
	ft_lstadd_back(cmd_list, *new_cmds);
	free(new_cmds);
	return (1);
}

static int	sort_three(t_stacks *s, t_list **cmds)
{
	t_cmd *cmd_ptr;
	t_list *new;

	if (!is_ordered(s->a))
	{
		cmd_ptr = malloc(sizeof(t_cmd));
		if (!cmd_ptr)
			return (-1);
		*cmd_ptr = SA;
		new = ft_lstnew(cmd_ptr);
		if (!new)
		{
			free(cmd_ptr);
			return (-1);
		}
		stack_exec_cmds(s, new);
		ft_lstadd_back(cmds, new);
	}
	rotate_a_min_on_top(s, cmds);
	return (1);
}

static t_list **turksort(t_stacks *s)
{
	t_list **cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	if (rev_sort_into_b(s, cmds) < 0)
		return (NULL);
	if (rotate_b_max_on_top(s, cmds) < 0)
		return (NULL);
	if (sort_three(s, cmds) < 0)
		return (NULL);
	if (push_all_to_a(s, cmds) < 0)
		return (NULL);
	return (cmds);
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
	t_list		**cmds;

	cmds = turksort(s);
	if (!cmds)
		return (-1);
	ft_lstiter(*cmds, &write_cmd);
	ft_lstclear(cmds, &free);
	free(cmds);
	return (0);
}
