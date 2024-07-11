/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:41:05 by pleander          #+#    #+#             */
/*   Updated: 2024/07/10 15:37:57 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/ft_printf.h"
#include "libft/include/libft.h"
#include "checker_bonus.h"

static char	*free_args_and_return_null(void *a1, void *a2)
{
	if (a1)
		free(a1);
	if (a2)
		free(a2);
	return (NULL);
}

static char	*join_args(int ac, char **av)
{
	int		i;
	int		c;
	char	*a1;
	char	*a2;

	a1 = ft_strdup(av[0]);
	if (!a1)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		c = ft_snprintf((void *) NULL, 0, "%s %s", a1, av[i]);
		a2 = ft_calloc(c + 1, sizeof(char));
		if (!a2)
			return (free_args_and_return_null((void *)a1, NULL));
		if (ft_snprintf(a2, c + 1, "%s %s", a1, av[i]) < 0)
			return (free_args_and_return_null((void *)a1, (void *)a2));
		free(a1);
		a1 = a2;
		i++;
	}
	return (a1);
}

static int	count_nums(char *arr)
{
	int		i;
	char	prev;

	prev = ' ';
	i = 0;
	while (*arr)
	{
		if (!ft_isdigit(prev) && ft_isdigit(*arr))
			i++;
		prev = *arr;
		arr++;
	}
	return (i);
}

static int	*char_arr_to_int_arr(int *nums, char *c_arr)
{
	int		i;
	int		*i_arr;
	char	**s_arr;

	*nums = count_nums(c_arr);
	i_arr = ft_calloc(*nums, sizeof(int));
	if (!i_arr)
		return (NULL);
	s_arr = ft_split(c_arr, ' ');
	if (!s_arr)
		return ((int *)free_args_and_return_null((void *)i_arr, NULL));
	i = 0;
	while (s_arr[i])
	{
		i_arr[i] = ft_atoi(s_arr[i]);
		if (overflowed(s_arr[i], i_arr[i]))
		{
			free_array((void **)s_arr);
			return ((int *)free_args_and_return_null((void *)i_arr, NULL));
		}
		i++;
	}
	free_array((void **)s_arr);
	return (i_arr);
}

int	*parse_args(int *nums, int ac, char **av)
{
	char	*arr;
	int		*i_arr;

	arr = join_args(ac, av);
	if (!arr)
		return (NULL);
	i_arr = char_arr_to_int_arr(nums, arr);
	free(arr);
	if (!i_arr)
		return (NULL);
	if (is_unique(i_arr, *nums) < 0)
	{
		free(i_arr);
		return (NULL);
	}
	return (i_arr);
}
