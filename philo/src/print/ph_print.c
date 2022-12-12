/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:41:00 by misimon           #+#    #+#             */
/*   Updated: 2022/12/12 15:14:36 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ph_print(t_philo philo, char *action)
{
	if (philo.rules->finish == FALSE)
	{
		pthread_mutex_lock(&philo.rules->writing);
		if (philo.rules->finish == FALSE)
			printf("%lldms %zu %s !\n", get_time() - philo.rules->starting_time,
				philo.id, action);
		pthread_mutex_unlock(&philo.rules->writing);
	}
}

void	ph_print_dead(t_philo philo, char *action)
{
	if (philo.rules->finish == TRUE)
	{
		pthread_mutex_lock(&philo.rules->writing);
		printf("%lldms %zu %s !\n", get_time() - philo.rules->starting_time
			+ philo.rules->time_die, philo.id, action);
		pthread_mutex_unlock(&philo.rules->writing);
	}
}
