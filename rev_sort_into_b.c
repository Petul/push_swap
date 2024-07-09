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
#include "libft/include/ft_printf.h"
#include "libft/include/libft.h"
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
	if (s->len < 2)
		return (0);
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

	insert_ind = find_rev_sort_ind(s->b, s->a->arr[index]); // Find insert index in B
	if (insert_ind < 0)
		return (NULL);
	top_dsts = get_dists_to_top(s, index, insert_ind);
	cmd_list = construct_insertion_cmd(top_dsts);
	free(top_dsts);
	return (cmd_list);
}

/* Finds the chain of commands for the optimal move for an element from A to B */
// static t_list **find_optimal_cmds(t_stacks *s)
// {
// 	t_list	**new;
// 	t_list	**min_lst;
// 	size_t	min_size;
// 	size_t	i;
//
// 	i = 0;
// 	new = get_cheapest_insert(s, i);
// 	min_lst = malloc(sizeof(t_list *));
// 	if (!min_lst || !new)
// 		return (NULL);
// 	*min_lst = *new;
// 	min_size = ft_lstsize(*new);
// 	free(new);
// 	while (i < s->a->len)
// 	{
// 		new = get_cheapest_insert(s, i);
// 		if (ft_lstsize(*new) < (int)min_size)
// 		{
// 			ft_lstclear(min_lst, &free);
// 			*min_lst = *new;
// 			min_size = ft_lstsize(*new);
// 		}
// 		else
// 			ft_lstclear(new, &free);
// 		free(new);
// 		i++;
// 	}
// 	return (min_lst);
// }
/* Finds the chain of commands for the optimal move for an element from A to B */
static int	find_optimal_cmds(t_stacks *s, t_list **optimal)
{
	t_list	**new;
	int		min_size;
	size_t	i;

	i = 0;
	min_size = -1;
	while (i < s->a->len)
	{
		new = get_cheapest_insert(s, i);
		if (!new)
			return (-1);
		if (min_size < 0 || ft_lstsize(*new) < min_size)
		{
			if ((*optimal))
				ft_lstclear(optimal, &free);
			*optimal = *new;
			min_size = ft_lstsize(*new);
		}
		else
			ft_lstclear(new, &free);
		free(new);
		i++;
	}
	return (min_size);
}

int	rev_sort_into_b(t_stacks *s, t_list **cmd_list)
{
	t_list	**optimal;
	int		optimal_len;

	optimal = ft_calloc(1, sizeof(t_list *));
	if (!optimal)
		return (-1);
	while (s->a->len > 3)
	{
		optimal_len = find_optimal_cmds(s, optimal);
		if (optimal_len < 0)
			return (-1);
		stack_exec_cmds(s, *optimal);
		ft_lstiter(*optimal, &write_cmd);
		ft_lstadd_back(cmd_list, *optimal);
		//free(optimal);
	}
	free(optimal);
	return (1);	
}
