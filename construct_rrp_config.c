/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_rrp_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:41:54 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 10:42:08 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	assign_cmds(t_cmd cmds[3], t_cmd a, t_cmd b, t_cmd c)
{
	cmds[0] = a;
	cmds[1] = b;
	cmds[2] = c;
}

static void	assign_rots(size_t rots[3], size_t a, size_t b, size_t c)
{
	rots[0] = a;
	rots[1] = b;
	rots[2] = c;
}

void	construct_rrp_config(t_rrp_config *c)
{
	size_t	com_rots;

	if (c->rot1 == c->rot2)
	{
		com_rots = min(c->a_size, c->b_size);
		assign_rots(c->rots, com_rots, c->a_size - com_rots,
			c->b_size - com_rots);
		if (c->rot1 > 0)
			assign_cmds(c->cmds, RR, RA, RB);
		else
			assign_cmds(c->cmds, RRR, RRA, RRB);
	}
	else
	{
		assign_rots(c->rots, c->a_size, c->b_size, 0);
		if (c->rot1 > 0)
			c->cmds[0] = RA;
		else
			c->cmds[0] = RRA;
		if (c->rot2 > 0)
			c->cmds[1] = RB;
		else
			c->cmds[1] = RRB;
	}
}
