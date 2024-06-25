/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:43:42 by pleander          #+#    #+#             */
/*   Updated: 2024/06/25 11:52:18 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include <stddef.h>

typedef struct s_stack
{
	int *arr;
	size_t start;
	size_t len;

}	t_stack;

int	*parse_args(int *nums, int ac, char **av);
int str_is_digit_and_space(char *str);

#endif

