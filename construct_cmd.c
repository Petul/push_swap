/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:50:03 by pleander          #+#    #+#             */
/*   Updated: 2024/07/03 14:01:25 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft/include/libft.h"
#include "push_swap.h"

static t_list *lst_new_cmd(t_cmd cmd)
{
	t_list	*lst;
	t_cmd	*cmd_ptr;

	cmd_ptr = malloc(sizeof(t_cmd));
	if (!cmd_ptr)
		return (NULL);
	*cmd_ptr = cmd;
	lst = ft_lstnew(cmd_ptr);
	if (!lst)
	{
		free(cmd_ptr);
		return (NULL);
	}
	return (lst);
}

static int	append_n_cmds(t_list **cmd_list, t_cmd cmd, size_t n)
{
	size_t	i;
	t_list	*new;
	t_list	*last;

	last = NULL;
	i = 0;
	while (i < n)
	{
		new = lst_new_cmd(cmd);
		if (!new)
			return (-1);
		if (!last)
			ft_lstadd_back(cmd_list, new);
		else
			last->next = new;
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

static void assign_cmds(t_cmd cmds[3], t_cmd a, t_cmd b, t_cmd c)
{
	cmds[0] = a;
	cmds[1] = b;
	cmds[2] = c;
}

static void assign_rots(size_t rots[3], size_t a, size_t b, size_t c)
{
	rots[0] = a;
	rots[1] = b;
	rots[2] = c;
}

static void	construct_rrp_config(size_t rots[3], t_cmd cmds[3], int r[2], size_t sz[2])
{
	size_t common_rots;
	
	if (r[0] == r[1])
	{
		common_rots = min(sz[0], sz[1]);
		assign_rots(rots, common_rots, sz[0] - common_rots, sz[1] - common_rots);
		if (r[0] > 0)
			assign_cmds(cmds, RR, RA, RB);
		else
			assign_cmds(cmds, RRR, RRA, RRB);
	}
	else 
	{
		assign_rots(rots, sz[0], sz[1], 0);
		if (r[0] > 0)
			cmds[0] = RA;
		else
			cmds[0] = RRA;
		if (r[1] > 0)
			cmds[1] = RB;
		else
			cmds[1] = RRB;
	}
}

static void	*free_list_and_return_null(t_list **list)
{
	ft_lstclear(list, &free);
	free(list);
	return (NULL);
}

static	t_list	**construct_rrp(int r1, int r2, size_t a, size_t b)
{
	t_list	**cmd_list;
	size_t	rots[3];
	t_cmd	cmds[3];
	int		i;
	int		r[2];
	size_t	sz[2];

	r[0] = r1;
	r[1] = r2;
	sz[0] = a;
	sz[1] = b;
	construct_rrp_config(rots, cmds, r, sz);
	cmd_list = ft_calloc(1, sizeof(t_list *));
	if (!cmd_list)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (rots[i] > 0 && append_n_cmds(cmd_list, cmds[i], rots[i]) < 0)
			return(free_list_and_return_null(cmd_list));
		i++;
	}
	if (append_n_cmds(cmd_list, PB, 1) < 0)
		return(free_list_and_return_null(cmd_list));
	return (cmd_list);
}

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
	size_t min_i;

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
