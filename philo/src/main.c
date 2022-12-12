/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by misimon           #+#    #+#             */
/*   Updated: 2022/12/12 16:10:12 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_all(t_ph *ph)
{
	size_t	i;

	i = 0;
	while (i < ph->nbr_philo)
	{
		pthread_join(ph->philo[i].thread, NULL);
		pthread_mutex_destroy(&ph->philo[i].fork);
		i++;
	}
	pthread_mutex_destroy(&ph->writing);
	free(ph->philo);
	free(ph);
}

void	start_eating(t_philo philo)
{
	lock_fork(philo);
	philo.last_eat = get_time();
	if (philo.rules->finish == FALSE)
		ph_print(philo, "is eating");
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
		lock_fork(philo);
		if (check_death(philo) == TRUE)
			break ;
		philo.last_eat = get_time();
		ph_print(philo, "is eating");
		philo.total_eat++;
		ft_sleep(philo.rules->time_eat);
		unlock_fork(philo);
		if (philo.rules->nbr_eat != 0 && philo.total_eat == philo.rules->nbr_eat)
			break ; 
		ph_print(philo, "is sleeping");
		ft_sleep(philo.rules->time_sleep);
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
