/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:44:09 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 12:00:25 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stddef.h>

typedef struct s_stack
{
	int		*arr;
	size_t	size;
	size_t	len;

}	t_stack;

typedef struct s_stacks
{
	t_stack	*a;
	t_stack	*b;
}	t_stacks;

typedef enum e_cmd
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}	t_cmd;

t_stacks	*create_stacks(int ac, char **av);
void		delete_stack(t_stack *stack);
int			str_is_digit_and_space(char *str);
t_stack		*create_stack(size_t size, size_t len, int *num_array);
int			*parse_args(int *nums, int ac, char **av);
int			overflowed(char *s, int n);
void		free_array(void **arr);
int			is_unique(int *i_arr, int nums);


#endif
