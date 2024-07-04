/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_in_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:02:36 by pleander          #+#    #+#             */
/*   Updated: 2024/07/04 15:22:32 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "push_swap.h"
#include <stdlib.h>

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
/* Swaps the top elements of stack A if they are not sorted */
static int	sort_a_top_elements(t_stacks *s, t_list **cmds)
{
	t_cmd *cmd_ptr;
	t_list *new;

	if (s->a->arr[0] < s->a->arr[1] || s->a->arr[1] == 1)
		return (1);
	cmd_ptr = malloc(sizeof(t_cmd));
	if (!cmd_ptr)
		return (-1);
	*cmd_ptr = SA;
	new = ft_lstnew(cmd_ptr);
	if (!new)
	{
		free(cmd_ptr);
		return (-1);
	}
	stack_exec_cmds(s, new);
	ft_lstadd_back(cmds, new);
	return (1);
}

static int	rotate_a(t_stacks *s, t_list **cmds)
{
	t_cmd *cmd_ptr;
	t_list *new;

	cmd_ptr = malloc(sizeof(t_cmd));
	if (!cmd_ptr)
		return (-1);
	*cmd_ptr = RRA;
	new = ft_lstnew(cmd_ptr);
	if (!new)
	{
		free(cmd_ptr);
		return (-1);
	}
	stack_exec_cmds(s, new);
	ft_lstadd_back(cmds, new);
	return (1);

}

t_list **sort_in_place(t_stacks *s)
{
	t_list **cmds;

	cmds = ft_calloc(1, sizeof(t_list *));
	if (!cmds)
		return (NULL);
	while (!is_ordered(s->a))
	{
		//print_stack(s->a);
		if (sort_a_top_elements(s, cmds) < 0)
		{
			ft_lstclear(cmds, &free); 
			free(cmds);
			return (NULL);
		}
		if (is_sorted(s->a))
			break ;
		if (rotate_a(s, cmds) < 0 )
		{
			ft_lstclear(cmds, &free); 
			free(cmds);
			return (NULL);
		}
		//print_stack(s->a);
	}
	rotate_a_min_on_top(s, cmds);
	return (cmds);
}
