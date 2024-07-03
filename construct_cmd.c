/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:50:03 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 19:36:41 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft/include/libft.h"
#include <stdio.h> //
#include "push_swap.h"

static int	append_n_cmds(t_list **cmd_list, t_cmd cmd, size_t n)
{
	size_t	i;
	t_list *new;
	t_cmd *cmd_ptr;
	t_list *last;

	last = NULL;
	i = 0;
	while (i < n)
	{
		cmd_ptr = malloc(sizeof(t_cmd));
		if (!cmd_ptr)
			return (-1);
		*cmd_ptr = cmd;
		new = ft_lstnew(cmd_ptr);
		if (!new)
		{
			//clear array
			//free(cmd_ptr);
			return (-1);
		}
		if (!last)
		{
			ft_lstadd_back(cmd_list, new);
		}
		else
		{
			last->next = new;
		}
		last = new;
		i++;
	}
	return (1);
}

/* Replaces ra and rb pairs with rr and
 * rra and rrb pairs with rrr
 */
static	size_t min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}
/* r1 and r2 determine what direction the array is rotated
 * > 0 normal rotation
 * <= reverse rotation
 */
static	t_list	**construct_rrp(int r1, int r2, size_t a, size_t b)
{
	t_list	**cmd_list;
	size_t	common_rotations;

	cmd_list = ft_calloc(1, sizeof(t_list *));
	if (!cmd_list)
		return (NULL);
	if (r1 == r2)
	{
		common_rotations = min(a, b);
		if (r1 > 0)
		{
			if (append_n_cmds(cmd_list, RR, common_rotations) < 0)
			{
				//free stuff
				return (NULL);
			}
			if (append_n_cmds(cmd_list, RA, a - common_rotations) < 0)
			{
				//free stuff
				return (NULL);
			}
			if (append_n_cmds(cmd_list, RB, b - common_rotations) < 0)
			{
				//free stuff
				return (NULL);
			}
		}
		else
		{
			if (append_n_cmds(cmd_list, RRR, common_rotations) < 0)
			{
				//free stuff
				return (NULL);
			}
			if (append_n_cmds(cmd_list, RRA, a - common_rotations) < 0)
			{
				//free stuff
				return (NULL);
			}
			if (append_n_cmds(cmd_list, RRB, b - common_rotations) < 0)
			{
				//free stuff
				return (NULL);
			}
		}
	}
	else
	{	
		if (r1 > 0)
		{
			if (append_n_cmds(cmd_list, RA, a) < 0)
			{
				//free everything
				return (NULL);
			}
		}
		else
		{
			if (append_n_cmds(cmd_list, RRA, a) < 0)
			{
				//free everything
				return (NULL);
			}
		}
		if (r2 > 0)
		{
			if (append_n_cmds(cmd_list, RB, b) < 0)
			{
				//free everything
				return (NULL);
			}
		}
		else
		{
			if (append_n_cmds(cmd_list, RRB, b) < 0)
			{
				//free everything
				return (NULL);
			}
		}
	}
	if (append_n_cmds(cmd_list, PB, 1) < 0)
	{
		//free everything
		return (NULL);
	}
	return (cmd_list);
}

#define RR_DIST(a, b) min(a, b) + (a - min(a,b)) + (b - min(a,b))
static size_t	calculate_index_of_shortest_insert(size_t *top_dsts)
{
	size_t shortest[2]; // 0: index, 1: len
	
	shortest[0] = 0;
	shortest[1] = RR_DIST(top_dsts[0], top_dsts[2]);
	if (top_dsts[0] + top_dsts[3] < shortest[1])
	{
		shortest[0] = 1;
		shortest[1] = top_dsts[0] + top_dsts[3];
	}
	if (top_dsts[1] + top_dsts[2] < shortest[1])
	{
		shortest[0] = 2;
		shortest[1] = top_dsts[1] + top_dsts[2];
	}
	if (RR_DIST(top_dsts[1], top_dsts[3]) < shortest[1])
	{
		shortest[0] = 3;
		shortest[1] = RR_DIST(top_dsts[1], top_dsts[3]);
	}
	return (shortest[0]);
}

/* Finds the optimal insertion command and returns it as a list
 * a: stack a and b rotated normally
 * b: stack a rotated normally and b reverse retated
 * c: stack b rotated normally and a reverse rotated
 * d: stack a and b reverse rotated 
 */
t_list	**construct_insertion_cmd(size_t *top_dsts)
{
	t_list	**cmd;
	size_t min_i;

	min_i = calculate_index_of_shortest_insert(top_dsts);
	if (min_i == 0)
		cmd = construct_rrp(1, 1, top_dsts[0], top_dsts[2]);
	else if (min_i == 1)
		cmd = construct_rrp(1, -1, top_dsts[0], top_dsts[3]);
	else if (min_i == 2)
		cmd = construct_rrp(-1, 1, top_dsts[1], top_dsts[2]);
	else if (min_i == 3)
		cmd = construct_rrp(-1, -1, top_dsts[1], top_dsts[3]);
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_list **construct_n_cmd(t_cmd cmd, size_t n)
{
	t_list **cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	if (append_n_cmds(cmds, cmd, n) < 0)
	{
		free(cmds);
		return (NULL);
	}
	return (cmds);
}
