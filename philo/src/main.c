/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by misimon           #+#    #+#             */
/*   Updated: 2022/12/16 09:52:07 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_all(t_ph *ph)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&ph->writing);
	pthread_mutex_destroy(&ph->check_eating);
	while (i < ph->nbr_philo)
	{
		pthread_join(ph->philo[i].thread, NULL);
		pthread_mutex_destroy(&ph->philo[i].fork);
		i++;
	}
	free(ph->philo);
	free(ph);
}

void	philo_eating(t_philo *philo)
{
	lock_fork(philo);
	if (philo->rules->nbr_philo != 1)
	{
		pthread_mutex_lock(&philo->rules->check_eating);
		ph_print(philo, "is eating");
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->rules->check_eating);
		if (philo->rules->finish == TRUE)
		{
			unlock_fork(philo);
			return ;
		}
		ft_sleep(philo->rules->time_eat);
		philo->total_eat++;
	}
	unlock_fork(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_sleep(philo->rules->time_sleep);
	while (philo->rules->finish == FALSE)
	{
		philo_eating(philo);
		if (philo->rules->finish == TRUE)
			break ;
		if ((philo->rules->nbr_eat != 0 && philo->total_eat
				== philo->rules->nbr_eat))
		{
			philo->rules->all_eat++;
			break ;
		}
		if (philo->rules->nbr_philo == 1)
			ft_sleep(philo->rules->time_die + 100);
		ph_print(philo, "is sleeping");
		ft_sleep(philo->rules->time_sleep);
		ph_print(philo, "is thinking");
	}
	return (0);
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
