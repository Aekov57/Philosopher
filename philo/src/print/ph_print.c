/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:41:00 by misimon           #+#    #+#             */
/*   Updated: 2022/12/06 18:17:34 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ph_print(t_time time, t_ph *ph, size_t i, char *action)
{
	if (ph->finish == 0)
	{
		pthread_mutex_lock(&ph->writing);
		if (ph->finish == 0)
			printf("%lldms %zu %s !\n", time, ph->philo[i].id, action);
		pthread_mutex_unlock(&ph->writing);
	}
}

void	ph_print_dead(t_time time, t_ph *ph, size_t i, char *action)
{
	if (ph->finish == 1)
	{
		pthread_mutex_lock(&ph->writing);
		printf("%lldms %zu %s !\n", time, ph->philo[i].id, action);
		pthread_mutex_unlock(&ph->writing);
	}
}
