/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkDeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:34:54 by misimon           #+#    #+#             */
/*   Updated: 2022/12/12 15:23:24 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

t_bool	time_range(t_philo philo)
{
	return (get_time() - philo.last_eat >= philo.rules->time_die);
}

t_bool	check_death(t_philo philo)
{
	if ((time_range(philo) && philo.rules->finish == FALSE)
		|| philo.rules->nbr_philo == 1)
	{
		philo.rules->finish = TRUE;
		ph_print_dead(philo, "died");
		return (TRUE);
	}
	return (FALSE);
}
