/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:01:02 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 16:45:05 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/ft_printf.h"
#include "push_swap.h"

/* Frees a null terminated array */
void	free_array(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

/* Checks if the str is composed of only valid sequenecs*/
int	str_is_valid(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_strchr(" -", str[i]))
			return (0);
		if (i != 0)
		{
			if (str[i] == '-' && !ft_isspace(str[i - 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

void	write_cmd(void *content)
{
	t_cmd	*c;

	c = (t_cmd *)content;
	if (*c == SA)
		ft_printf("sa\n");
	else if (*c == SB)
		ft_printf("sb\n");
	else if (*c == SS)
		ft_printf("ss\n");
	else if (*c == PA)
		ft_printf("pa\n");
	else if (*c == PB)
		ft_printf("pb\n");
	else if (*c == RA)
		ft_printf("ra\n");
	else if (*c == RB)
		ft_printf("rb\n");
	else if (*c == RR)
		ft_printf("rr\n");
	else if (*c == RRA)
		ft_printf("rra\n");
	else if (*c == RRB)
		ft_printf("rrb\n");
	else if (*c == RRR)
		ft_printf("rrr\n");
}
