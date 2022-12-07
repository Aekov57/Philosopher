/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by misimon           #+#    #+#             */
/*   Updated: 2022/12/07 19:10:32 by misimon          ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_ph	*ph;
	size_t	i;

	ph = (t_ph *)arg;
	i = ph->position;
	if (i % 2 == 0)
		usleep(10);
	while (ph->finish == 0)
	{
		lock_fork(ph, i);
		if (check_death(ph, i) == TRUE)
			break ;
		ph->philo[i].last_eat = get_time();
		ph_print(get_time() - ph->starting_time, ph, i, "is eating");
		ft_sleep(ph->time_eat, get_time());
		if (ph->nbr_eat != 0)
			ph->philo[i].total_eat++;
		unlock_fork(ph, i);
		if (ph->nbr_eat != 0 && ph->philo[i].total_eat == ph->nbr_eat)
			break ;
		ph_print(get_time() - ph->starting_time, ph, i, "is sleeping");
		ft_sleep(ph->time_sleep, get_time());
		ph_print(get_time() - ph->starting_time, ph, i, "is thinking");
	}
	return (0);
}

void	create_routine(t_ph *ph)
{
	ph->position = 0;
	ph->starting_time = get_time();
	while (ph->position < ph->nbr_philo)
	{
		pthread_create(&ph->philo[ph->position].thread, 0, routine, (void *)ph);
		usleep(100);
		ph->position++;
	}
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
