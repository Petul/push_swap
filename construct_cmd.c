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

/* Finds the optimal insertion command and returns it as a list
 * a: stack a and b rotated normally
 * b: stack a rotated normally and b reverse retated
 * c: stack b rotated normally and a reverse rotated
 * d: stack a and b reverse rotated 
 */
t_list	**construct_insertion_cmd(size_t *top_dsts)
{
	t_list **cmds[4];
	t_list **shortest;
	size_t min_list[4];
	size_t min_i;
	size_t i;

	cmds[0] = construct_rrp(1, 1, top_dsts[0], top_dsts[2]);
	cmds[1] = construct_rrp(1, -1, top_dsts[0], top_dsts[3]);
	cmds[2] = construct_rrp(-1, 1, top_dsts[1], top_dsts[2]);
	cmds[3] = construct_rrp(-1, -1, top_dsts[1], top_dsts[3]);
	min_list[0] = ft_lstsize(*cmds[0]);
	min_list[1] = ft_lstsize(*cmds[1]);
	min_list[2] = ft_lstsize(*cmds[2]);
	min_list[3] = ft_lstsize(*cmds[3]);
	min_i = get_min_index(min_list, 4);
	shortest = cmds[min_i];
	i = 0;
	while (i < 4)
	{
		if (i != min_i)
		{
			ft_lstclear(cmds[i], &free);
			free(cmds[i]);
		}
		i++;
	}
	return (shortest);
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
