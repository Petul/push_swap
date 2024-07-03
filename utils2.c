/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:44:42 by pleander          #+#    #+#             */
/*   Updated: 2024/07/03 15:18:47 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Checks if the stack is fully sorted i.e. smallest element on top and largest
* last */
int	is_sorted(t_stack *s)
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

/* Checks if the stack is ordered correctly i.e. only needs to be rotated to
* become sorted */
int is_ordered(t_stack *s)
{
	size_t	i;
	int		n;
	int		max_f;

	n = s->arr[0];
	max_f = 0;
	i = 1;
	while (i < s->len)
	{
		if (s->arr[i] <= n)
		{
			if (max_f == 1)
				return (0);
			else
				max_f = 1;
		}
		n = s->arr[i];
		i++;
	}
	if (n <= s->arr[0])
		return (1);
	return (0);

}
