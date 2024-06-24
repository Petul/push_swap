/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:23:18 by pleander          #+#    #+#             */
/*   Updated: 2024/06/24 15:39:26 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include "push_swap.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Error\n");
		return (1);
	}
}

static t_stack* create_stack(char **argv)
{
	
}

/* Checks if the str is a digit */
static int str_is_digit(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
