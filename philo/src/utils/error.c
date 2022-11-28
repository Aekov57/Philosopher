/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:02:12 by misimon           #+#    #+#             */
/*   Updated: 2022/11/28 20:09:09 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	write_error(char *str)
{
	write(2, "ERROR: ", 7);
	write(2, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

void	*null_error(char *str)
{
	write(2, "ERROR: ", 7);
	write(2, str, ft_strlen(str));
	return (NULL);
}