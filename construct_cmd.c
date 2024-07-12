/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:50:03 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 10:45:52 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft/include/libft.h"
#include "push_swap.h"

static void	*free_list_and_return_null(t_list **list)
{
	ft_lstclear(list, &free);
	free(list);
	return (NULL);
}

static t_list	**construct_rrp(int r1, int r2, size_t a, size_t b)
{
	t_rrp_config	c;
	t_list			**cmd_list;
	int				i;

	c.rot1 = r1;
	c.rot2 = r2;
	c.a_size = a;
	c.b_size = b;
	construct_rrp_config(&c);
	cmd_list = ft_calloc(1, sizeof(t_list *));
	if (!cmd_list)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (c.rots[i] > 0
			&& append_cmd_to_cmds(c.cmds[i], cmd_list, c.rots[i]) < 0)
			return (free_list_and_return_null(cmd_list));
		i++;
	}
	if (append_cmd_to_cmds(PB, cmd_list, 1) < 0)
		return (free_list_and_return_null(cmd_list));
	return (cmd_list);
}

/* Find the shortest insertion from A to B 
 * shortest = 0: index, 1: len */
static size_t	calculate_index_of_shortest_insert(size_t *top_dsts)
{
	size_t	shortest[2];

	shortest[0] = 0;
	shortest[1] = rr_dist(top_dsts[0], top_dsts[2]);
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
	if (rr_dist(top_dsts[1], top_dsts[3]) < shortest[1])
	{
		shortest[0] = 3;
		shortest[1] = rr_dist(top_dsts[1], top_dsts[3]);
	}
	return (shortest[0]);
}

/*
 * Finds the optimal insertion command and returns it as a list
 * a: stack a and b rotated normally
 * b: stack a rotated normally and b reverse retated
 * c: stack b rotated normally and a reverse rotated
 * d: stack a and b reverse rotated 
 */
t_list	**construct_insertion_cmd(size_t *top_dsts)
{
	t_list	**cmd;
	size_t	min_i;

	cmd = NULL;
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

t_list	**construct_n_cmd(t_cmd cmd, size_t n)
{
	t_list	**cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	if (append_cmd_to_cmds(cmd, cmds, n) < 0)
	{
		free(cmds);
		return (NULL);
	}
	return (cmds);
}
