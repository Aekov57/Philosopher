/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkHandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:18:29 by misimon           #+#    #+#             */
/*   Updated: 2022/12/06 18:08:28 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	lock_fork(t_ph *ph, size_t i)
{
	pthread_mutex_lock(&ph->philo[i].fork);
	ph_print(get_time() - ph->starting_time, ph, i, "has taken a fork");
	if (i + 1 > ph->nbr_philo && ph->nbr_philo != 1)
		pthread_mutex_lock(&ph->philo[0].fork);
	else
		pthread_mutex_lock(&ph->philo[i + 1].fork);
	if (ph->nbr_philo != 1)
		ph_print(get_time() - ph->starting_time, ph, i, "has taken a fork");
}

void	unlock_fork(t_ph *ph, size_t i)
{
	pthread_mutex_unlock(&ph->philo[i].fork);
	if (i + 1 > ph->nbr_philo)
		pthread_mutex_unlock(&ph->philo[0].fork);
	else
		pthread_mutex_unlock(&ph->philo[i + 1].fork);
}
