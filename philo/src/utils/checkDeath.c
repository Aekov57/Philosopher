/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkDeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:34:54 by misimon           #+#    #+#             */
/*   Updated: 2022/12/16 09:43:28 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	death_checker(t_ph *ph)
{
	size_t	i;

	while (ph->finish == FALSE && ph->all_eat != ph->nbr_philo)
	{
		i = 0;
		while (i < ph->nbr_philo && ph->finish == FALSE)
		{
			pthread_mutex_lock(&ph->check_eating);
			if ((get_time() - ph->philo[i].last_eat > ph->time_die))
			{
				ph->finish = TRUE;
				ph_print_dead(&ph->philo[i], "is dead");
			}
			pthread_mutex_unlock(&ph->check_eating);
			i++;
		}
		usleep(50);
	}
}
