/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:51:09 by misimon           #+#    #+#             */
/*   Updated: 2022/12/05 14:28:12 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

t_bool	check_value(t_ph *ph)
{
	if (ph->nbr_philo == 0 || ph->time_die == 0 || ph->time_eat == 0 ||
		ph->time_sleep == 0)
		return (TRUE);
	return (FALSE);
}

void	give_value(t_ph *ph, int argc, char **argv)
{
	ph->nbr_philo = ft_atoi(argv[1]);
	ph->time_die = ft_atoi(argv[2]);
	ph->time_eat = ft_atoi(argv[3]);
	ph->time_sleep = ft_atoi(argv[4]);
	ph->finish = 0;
	if (argc > 5)
		ph->nbr_eat = ft_atoi(argv[5]);
	else
		ph->nbr_eat = 0;
}

t_ph	*init(int argc, char **argv)
{
	t_ph	*ph;

	ph = malloc(sizeof(t_ph));
	if (ph == NULL)
		return (null_error("MALLOC ALLOCATION FAILED !\n"));
	give_value(ph, argc, argv);
	if (check_value(ph) == TRUE)
	{
		free(ph);
		return (null_error("ARG IS NOT > 0 !\n"));
	}
	return (ph);
}
