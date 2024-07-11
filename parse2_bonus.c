/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:22:42 by pleander          #+#    #+#             */
/*   Updated: 2024/07/11 14:22:42 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_unique(int *i_arr, int nums)
{
	int	i;
	int	j;

	i = 0;
	while (i < nums)
	{
		j = 0;
		while (j < i)
		{
			if (i_arr[j] == i_arr[i])
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	overflowed(char *s, int n)
{
	if (s[0] == '-' && n >= 0)
		return (1);
	if (s[0] != '-' && n < 0)
		return (1);
	return (0);
}
