/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:58:40 by pleander          #+#    #+#             */
/*   Updated: 2024/07/03 16:30:54 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include "push_swap.h"

static	t_list **rotate_i_to_top(t_stack *s, size_t i, t_cmd rot, t_cmd rev_rot)
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

static int	rotate_a_min_on_top(t_stacks *s, t_list **cmd_list)
{
	t_list	**new_cmds;
	size_t	min_i;
	int		min_n;
	size_t	i;

	min_i = 0;
	min_n = s->a->arr[0];
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
	new_cmds = rotate_i_to_top(s->b, max_i, RB, RRB);
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

	new_cmds = construct_n_cmd(PA, s->b->len);
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

static t_list **sort_in_place(t_stacks *s)
{
	t_list **cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	if (is_ordered(s->a))
		rotate_a_min_on_top(s, cmds);
	if (is_sorted(s->a))
		return (cmds);

	return (NULL);
}

static t_list **turksort(t_stacks *s)
{
	t_list **cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	if (push_two_to_b(s, cmds) < 0)
	 	return (NULL);
	if (rev_sort_into_b(s, cmds) < 0)
		return (NULL);
	if (rotate_b_max_on_top(s, cmds) < 0)
		return (NULL);
	if (push_all_to_a(s, cmds) < 0)
		return (NULL);
	return (cmds);
}

static void	free_all(t_stacks *s1, t_stacks *s2, t_list **s1_cmds, t_list **s2_cmds)
{
	if (s1)
	{
		delete_stack(s1->a);
		delete_stack(s1->b);
		free(s1);
	}
	if (s2)
	{
		delete_stack(s2->a);
		delete_stack(s2->b);
		free(s2);
	}
	if (s1_cmds)
	{
		ft_lstclear(s1_cmds, &free);
		free(s1_cmds);
	}
	if (s2_cmds)
	{
		ft_lstclear(s2_cmds, &free);
		free(s2_cmds);
	}
}

static void	error_exit(t_stacks *s1, t_stacks *s2, t_list **s1_cmds, t_list **s2_cmds)
{
	free_all(s1, s2, s1_cmds, s2_cmds);
	ft_printf("Error\n");
	exit(1);
}
/*
*	1)	Push 2 elements from A to B
*	2)	Push elements one at a time from A to B so that they are in descending
*		order
*	3)	Rotate B so that largest element is at the top
*	4)	Push all elements to A
*/
int	push_swap(int n_args, char **args)
{
	t_stacks	*s1;
	t_stacks	*s2;
	t_list		**s1_cmds;
	t_list		**s2_cmds;

	s1 = NULL;
	s2 = NULL;
	s1_cmds = NULL;
	s2_cmds = NULL;
	s1 = create_stacks(n_args, args);
	s2 = create_stacks(n_args, args);
	if (!s1 || !s2)
		error_exit(s1, s2, s1_cmds, s2_cmds);
	s1_cmds = sort_in_place(s1);
	s2_cmds = turksort(s2);
	if (!s1_cmds || !s2_cmds)
		error_exit(s1, s2, s1_cmds, s2_cmds);
	if (ft_lstsize(*s1_cmds) < ft_lstsize(*s2_cmds))
		ft_lstiter(*s1_cmds, &write_cmd);
	else
		ft_lstiter(*s2_cmds, &write_cmd);
	free_all(s1, s2, s1_cmds, s2_cmds);
	return (1);
}
