/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:04:31 by misimon           #+#    #+#             */
/*   Updated: 2022/11/30 19:08:09 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

int	create_philo(t_ph *ph)
{
	size_t	i;

	ph->philo = malloc(sizeof(t_philo) * ph->nbr_philo);
	if (ph->philo == NULL)
		return (write_error("MALLOC ALLOCATION FAILED !\n"));
	i = 0;
	pthread_mutex_init(&ph->writing, NULL);
	while (i < ph->nbr_philo)
	{
		ph->philo[i].id = i + 1;
		if (pthread_mutex_init(&ph->philo[i].fork, NULL) != 0)
			return (write_error("MUTEX INIT FAILED !\n"));
		ph->philo[i].total_eat = 0;
		i++;
	}
	return (0);
}
