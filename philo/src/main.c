/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by misimon           #+#    #+#             */
/*   Updated: 2022/12/13 17:07:34 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_all(t_ph *ph)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&ph->writing);
	while (i < ph->nbr_philo)
	{
		pthread_join(ph->philo[i].thread, NULL);
		pthread_mutex_destroy(&ph->philo[i].fork);
		i++;
	}
	free(ph->philo);
	free(ph);
}

void philo_eating(t_philo philo)
{
	lock_fork(philo);
	ph_print(philo, "is eating");
	philo.last_eat = get_time();
	philo.total_eat++;
	ft_sleep(philo.rules->time_eat);
	unlock_fork(philo);
}

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	if (philo.id % 2 == 0)
		ft_sleep(philo.rules->time_sleep);
	while (philo.rules->finish == FALSE)
	{
		philo_eating(philo);
		if (philo.rules->nbr_eat != 0 && philo.total_eat == philo.rules->nbr_eat)
		{
			philo.rules->all_eat++;
			break ;
		}
		ph_print(philo, "is sleeping");
		ft_sleep(philo.rules->time_sleep);
		ph_print(philo, "is thinking");
	}
	return (0);
}

		// if (check_death(philo) == TRUE)
		// 	break ;

void death_checker(t_ph *ph)
{
	size_t	i;

	while (ph->finish == FALSE && ph->all_eat != ph->nbr_philo)
	{
		i = 0;
		while (i < ph->nbr_philo)
		{
			if (get_time() - ph->philo[i].last_eat >= ph->time_die)
			{
				pthread_mutex_unlock(&ph->writing);
				ph->finish = TRUE;
				ph_print_dead(ph->philo[i], "is dead");
				return ;
			}
			i++;
		}
		usleep(50);
	}
}

void	create_routine(t_ph *ph)
{
	size_t	i;

	i = -1;
	ph->starting_time = get_time();
	while (++i < ph->nbr_philo)
		pthread_create(&ph->philo[i].thread, 0, routine, &ph->philo[i]);
	death_checker(ph);
	clean_all(ph);
}

int	main(int argc, char **argv)
{
	t_ph	*ph;

	if (argc < 5 || argc > 6)
		return (write_error("YOU NEED 4 OR 5 ARG !\n"));
	ph = init(argc, argv);
	if (ph == NULL || create_philo(ph) > 0)
		return (EXIT_FAILURE);
	create_routine(ph);
	return (EXIT_SUCCESS);
}
