/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_sort_into_b2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:47:20 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 10:48:06 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "push_swap.h"

/* Calculates a cost matrix with costs for different rotation alternatives
 * to reach the desired result.
 * Returns [s_a rot, s_a rev_rot, s_b rot, s_b rev_rot]
 */
size_t	*get_dists_to_top(t_stacks *s, size_t i_a, size_t i_b)
{
	size_t	*dists;

	dists = ft_calloc(4, sizeof(size_t));
	if (!dists)
		return (NULL);
	dists[0] = i_a;
	dists[1] = s->a->len - i_a;
	dists[2] = i_b;
	dists[3] = s->b->len - i_b;
	return (dists);
}
