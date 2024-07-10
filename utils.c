/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:01:02 by pleander          #+#    #+#             */
/*   Updated: 2024/07/01 19:28:10 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
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

/* Checks if the str is composed of only digits and spaces*/
int	str_is_digit_and_space(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str) && !ft_strchr(" -", *str))
			return (0);
		str++;
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
