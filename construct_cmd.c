/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:50:03 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 15:21:08 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "push_swap.h"

static int	append_n_cmds(t_list **cmd_list, char *cmd, size_t n)
{
	size_t	i;
	t_list *new;

	i = 0;
	while (i < n)
	{
		new = ft_lstnew(cmd);
		if (!new)
		{
			//clear array
			return (-1);
		}
		ft_lstadd_back(cmd_list, new);
		i++;
	}
	return (1);
}

static	t_list	**construct_rot_rot(size_t a, size_t b)
{
	t_list	**cmd_list;

	cmd_list = ft_calloc(1, sizeof(t_list *));
	if (!cmd_list)
		return (NULL);
	if (append_n_cmds(cmd_list, "ra", a) < 0)
	{
		//free everything
		return (NULL);
	}
	if (append_n_cmds(cmd_list, "rb", b) < 0)
	{
		//free everything
		return (NULL);
	}
	if (append_n_cmds(cmd_list, "pb", 1) < 0)
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
	t_list **a_cmds;

	a_cmds = construct_rot_rot(top_dsts[0], top_dsts[2]);
	if (!a_cmds)
		return (NULL);
	return (a_cmds);
}

t_list **construct_n_cmd(char *cmd, size_t n)
{
	t_list **cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (append_n_cmds(cmds, cmd, n) < 0)
		return (NULL);
	return (cmds);
}
