/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:36:41 by pleander          #+#    #+#             */
/*   Updated: 2024/07/10 15:37:34 by pleander         ###   ########.fr       */
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
