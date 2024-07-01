/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_sort_into_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:32:20 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 15:33:44 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

/* Calculates a cost matrix with costs for different rotation alternatives
 * to reach the desired result. Returns [s_a rot, s_a rev_rot, s_b rot, s_b rev_rot]
 */
static size_t	*get_dists_to_top(t_stacks *s, size_t i_a, size_t i_b)
{
	size_t *dists;

	dists = ft_calloc(4, sizeof(size_t));
	if (!dists)
		return (NULL);
	dists[0] = i_a;
	dists[1] = s->a->len - i_a;
	dists[2] = i_b;
	dists[3] = s->b->len - i_b;

	return (dists);
}

/* Get index where number should be inserted so that the stack remains
 * sorted descendingly
 */
static ssize_t	find_rev_sort_ind(t_stack *s, int num)
{
	size_t	i;

	i = 0;
	while (i < s->len)
	{
		if (i == 0)
		{
			if (num > s->arr[0] && num <= s->arr[s->len - 1])
				return (0);
			if (s->arr[s->len - 1] < s->arr[0]) //  Max number
			{
				if (num > s->arr[0])
					return (0);
			}
			if (s->arr[s->len - 1] < s->arr[0]) //  Min number
			{
				if (num < s->arr[s->len - 1])
					return (0);
			}
		}
		else
		{
			if (num < s->arr[i - 1] && num >= s->arr[i])
				return (i);
			if (s->arr[i - 1] < s->arr[i]) //  Max number
			{
				if (num > s->arr[i])
					return (i);
			}
			if (s->arr[i - 1] < s->arr[i]) //  Min number
			{
				if (num < s->arr[i - 1])
					return (i);
			}
		}
		i++;
	}
	return (-1);
}

/* Calculates the cheapest way to insert index from stack A to stack B so that
* stack B remains in descending order
*
* The cost consists of 
* 1) Rotation of element to the top of stack A
* 2) Rotation of stack B to put correct location at the top
* 3) Pushing the element to stack B 
*/
static t_list **get_cheapest_insert(t_stacks *s, size_t index)
{
	t_list **cmd_list;
	ssize_t	insert_ind;
	size_t *top_dsts;

	insert_ind = find_rev_sort_ind(s->b, s->a->arr[index]);
	if (insert_ind < 0)
		return (NULL);
	top_dsts = get_dists_to_top(s, index, insert_ind);
	//printf("Top d for i=%zu :\n%5zu %2zu\n%5zu %2zu\n", index, top_dsts[0], top_dsts[2], top_dsts[1], top_dsts[3]);
	cmd_list = construct_insertion_cmd(top_dsts);
	free(top_dsts);
	return (cmd_list);
}

/* Finds the index of the value in stack A which is the cheapest one to move to stack B */
static ssize_t get_cheapest_index(t_stacks *s)
{
	t_list	**new;
	size_t	i;
	size_t	min_lst;
	size_t	min_ix;

	i = 0;
	new = get_cheapest_insert(s, i);
	if (!new)
		return (-1);
	min_lst = ft_lstsize(*new);
	min_ix = i;
	ft_lstclear(new, &do_nothing);
	free(new);
	while (i < s->a->len)
	{
		new = get_cheapest_insert(s, i);
		if (ft_lstsize(*new) < (int)min_lst)
			min_ix = i;
		ft_lstclear(new, &do_nothing);
		free(new);
		i++;
	}
	return (min_ix);
}

int	rev_sort_into_b(t_stacks *s, t_list **cmd_list)
{
	t_list	**new;
	ssize_t	min_ix;

	while (s->a->len > 0)
	{
		min_ix = get_cheapest_index(s);
		if (min_ix < 0)
			return (-1);
		new = get_cheapest_insert(s, min_ix);
		if (!new)
			return (-1);
		stack_exec_cmds(s, *new);
		ft_lstadd_back(cmd_list, *new);
		free(new);
	}
	return (1);	
}
