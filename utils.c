/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:01:02 by pleander          #+#    #+#             */
/*   Updated: 2024/06/25 11:03:13 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"

/* Checks if the str is composed of only digits and spaces*/
int str_is_digit_and_space(char *str)
 {
 	if (!str)
 		return (0);
 	while (*str)
 	{
 		if (!ft_isdigit(*str) && *str != ' ')
 			return (0);
 		str++;
 	}
 	return (1);
 }

