/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:27:05 by misimon           #+#    #+#             */
/*   Updated: 2022/11/28 18:56:20 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

t_bool	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

size_t	ft_atoi(const char *str)
{
	size_t	result;
	size_t	l;

	l = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			l = -1;
	while (ft_isdigit(*str) && result <= INT_MAX)
		result = result * 10 + *str++ - '0';
	result *= l;
	if (result > INT_MAX)
		return (0);
	return (result);
}
