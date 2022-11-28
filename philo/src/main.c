/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by misimon           #+#    #+#             */
/*   Updated: 2022/11/28 21:20:02 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void lock_fork(t_ph *ph, size_t i)
{
	pthread_mutex_lock(&ph->philo[i].fork);
	printf("ID: %zu - Taking fork\n", ph->philo[i].id);
	if (i + 1 >= ph->nbr_philo)
	{
		pthread_mutex_lock(&ph->philo[0].fork);
		printf("ID: %zu - Taking next fork from\n", ph->philo[0].id);
	}
	else
	{
		pthread_mutex_lock(&ph->philo[i + 1].fork);
		printf("ID: %zu - Taking next fork from\n", ph->philo[i].id);
	}
}

void unlock_fork(t_ph *ph, size_t i)
{
	pthread_mutex_unlock(&ph->philo[i].fork);
	if (i + 1 >= ph->nbr_philo)
		pthread_mutex_unlock(&ph->philo[0].fork);
	else
		pthread_mutex_unlock(&ph->philo[i + 1].fork);
}

void *routine(void *arg)
{
	t_ph *ph;
	size_t i;

	ph = (t_ph *)arg;
	i = ph->position;
	while (1)
	{
		lock_fork(ph, i);
		printf("ID: %zu - Is eating !\n", ph->philo[i].id);
		usleep(ph->time_eat * 1000);
		unlock_fork(ph, i);
	}
	return (0);
}

void	create_routine(t_ph *ph)
{
	ph->position = 0;
	while (ph->position < ph->nbr_philo)
	{
		pthread_create(&ph->philo[ph->position].thread, NULL, routine, (void *)ph);
		usleep(1);
		ph->position++;
	}
	size_t i = 0;
	while (i <= ph->nbr_philo)
	{
		pthread_join(ph->philo[i].thread, NULL);
		i++;
	}
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