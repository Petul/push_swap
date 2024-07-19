/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:23:32 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 13:34:44 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/include/get_next_line.h"
#include "libft/include/ft_printf.h"
#include "checker_bonus.h"

static t_cmd	get_cmd_from_line(char *line)
{
	if (!ft_strcmp(line, "ra\n"))
		return (RA);
	if (!ft_strcmp(line, "rra\n"))
		return (RRA);
	if (!ft_strcmp(line, "rb\n"))
		return (RB);
	if (!ft_strcmp(line, "rrb\n"))
		return (RRB);
	if (!ft_strcmp(line, "rr\n"))
		return (RR);
	if (!ft_strcmp(line, "rrr\n"))
		return (RRR);
	if (!ft_strcmp(line, "pa\n"))
		return (PA);
	if (!ft_strcmp(line, "pb\n"))
		return (PB);
	if (!ft_strcmp(line, "sa\n"))
		return (SA);
	if (!ft_strcmp(line, "sb\n"))
		return (SB);
	return (ERR);
}

/* Checks if the stack is fully sorted i.e. smallest element on top and largest
* last */
static int	is_sorted(t_stack *s)
{
	size_t	i;
	int		n;

	n = s->arr[0];
	i = 1;
	while (i < s->len)
	{
		if (s->arr[i] <= n)
			return (0);
		n = s->arr[i];
		i++;
	}
	return (1);
}

static int	free_and_return_negative(t_list **lst, char *line)
{
	ft_lstclear(lst, &free);
	free(lst);
	free(line);
	return (-1);
}

int	checker(t_stacks *s)
{
	char	*line;
	t_cmd	cmd;
	t_list	**cmd_lst;

	cmd_lst = ft_calloc(1, sizeof(t_cmd *));
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		cmd = get_cmd_from_line(line);
		if (cmd == ERR)
			return (free_and_return_negative(cmd_lst, line));
		if (append_cmd_to_cmds(cmd, cmd_lst, 1) < 0)
			return (free_and_return_negative(cmd_lst, line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	stack_exec_cmds(s, *cmd_lst);
	ft_lstclear(cmd_lst, &free);
	free(cmd_lst);
	if (is_sorted(s->a) && s->b->len == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (0);
}
