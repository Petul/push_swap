/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:58:40 by pleander          #+#    #+#             */
/*   Updated: 2024/06/26 16:44:50 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"

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
static size_t	get_insertion_ind(t_stack *s, int num)
{
	size_t	i;

	if (num > s->arr[0])
		return (0);
	i = 1;
	while (i < s->len)
	{
		if (num < s->arr[i - 1] && num >= s->arr[i])
			return (i);
		i++;
	}
	return (i);
}

void ft_putstr(void *str)
{
	ft_printf("%s\n", str);
	return ;
}

/* Calculates the cost to move an element from index in stack A to 
* the dec sorted location in stack b
*
* The cost consists of 
* 1) Rotation of element to the top of stack A
* 2) Rotation of stack B to put correct location at the top
* 3) Pushing the element to stack B (unnecessary as done for all)
*/
t_list **get_cheapest_insert(t_stacks *s, size_t index)
{
	t_list **cmd_list;
	size_t *top_dsts = get_dists_to_top(s, index, get_insertion_ind(s->b, s->a->arr[index]));
	//ft_printf("Top d:\n%5d %2d\n%5d %2d\n", top_dsts[0], top_dsts[2], top_dsts[1], top_dsts[3]);
	cmd_list = construct_insertion_cmd(top_dsts);

	// ft_printf("Stack A:\n");
	// print_stack(s->a);
	// ft_printf("Stack B:\n");
	// print_stack(s->b);
	//
	// ft_lstiter(*cmd_list, &ft_putstr);
	// stack_exec_cmds(s, *cmd_list);
	return (cmd_list);
}

static void do_nothing(void *p)
{
	if (p)
		return ;
	return ;
}

static size_t get_cheapest_index(t_stacks *s)
{
	t_list	**new;
	size_t	i;
	size_t	min_ix;

	i = 0;
	new = get_cheapest_insert(s, i);
	min_ix = ft_lstsize(*new);
	ft_lstclear(new, &do_nothing);
	while (i < s->a->len)
	{
		new = get_cheapest_insert(s, i);
		if (ft_lstsize(*new) < (int)min_ix)
			i = min_ix;
		ft_lstclear(new, &do_nothing);
		i++;
	}
	return (i);
}
int	push_swap(t_stacks *s)
{
	t_list	**cmd_list;
	t_list	**new;
	size_t	min_ix;

	cmd_list = ft_calloc(1, sizeof(t_list *));
	if (!cmd_list)
		return (-1);
	stack_push_n(s->b, s->a, 2);
	while (s->a->len > 0)
	{
		ft_printf("Stack A:\n");
		print_stack(s->a);
		ft_printf("Stack B:\n");
		print_stack(s->b);
		min_ix = get_cheapest_index(s);
		new = get_cheapest_insert(s, min_ix);
		ft_lstiter(*new, &ft_putstr);
		ft_putstr("\n");
		stack_exec_cmds(s, *new);
		ft_lstadd_back(cmd_list, *new);
		free(new);
	}

	return (1);
}
