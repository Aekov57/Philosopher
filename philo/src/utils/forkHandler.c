/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkHandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:18:29 by misimon           #+#    #+#             */
/*   Updated: 2022/12/15 14:48:44 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (philo->rules->finish == FALSE)
		ph_print(philo, "has taken a fork");
	if (philo->id + 1 > philo->rules->nbr_philo && philo->rules->nbr_philo != 1)
		pthread_mutex_lock(&philo->rules->philo[0].fork);
	else if (philo->id <= philo->rules->nbr_philo && philo->rules->nbr_philo
		!= 1)
		pthread_mutex_lock(&philo->rules->philo[philo->id].fork);
	if (philo->rules->nbr_philo != 1 && philo->rules->finish == FALSE)
		ph_print(philo, "has taken a fork");
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->id + 1 > philo->rules->nbr_philo)
		pthread_mutex_unlock(&philo->rules->philo[0].fork);
	else if (philo->id <= philo->rules->nbr_philo && philo->rules->nbr_philo
		!= 1)
		pthread_mutex_unlock(&philo->rules->philo[philo->id].fork);
}
