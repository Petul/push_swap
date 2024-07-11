/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:51:50 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 16:48:32 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"

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
