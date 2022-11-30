/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by misimon           #+#    #+#             */
/*   Updated: 2022/11/30 19:19:58 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_time	get_time(void)
{
	struct timeval	get_time;

	gettimeofday(&get_time, NULL);
	return (get_time.tv_sec * 1000 + get_time.tv_usec / 1000);
}

void	ph_print(t_time time, t_ph *ph, size_t i, char *action)
{
	pthread_mutex_lock(&ph->writing);
	printf("%lldms - %zu - %s !\n", time, ph->philo[i].id, action);
	pthread_mutex_unlock(&ph->writing);
}

void	lock_fork(t_ph *ph, size_t i)
{
	pthread_mutex_lock(&ph->philo[i].fork);
	ph_print(get_time() - ph->starting_time, ph, i, "is taking fork");
	if (i + 1 > ph->nbr_philo)
		pthread_mutex_lock(&ph->philo[0].fork);
	else
		pthread_mutex_lock(&ph->philo[i + 1].fork);
	ph_print(get_time() - ph->starting_time, ph, i, "is taking fork");
}

void	unlock_fork(t_ph *ph, size_t i)
{
	pthread_mutex_unlock(&ph->philo[i].fork);
	if (i + 1 > ph->nbr_philo)
		pthread_mutex_unlock(&ph->philo[0].fork);
	else
		pthread_mutex_unlock(&ph->philo[i + 1].fork);
}

void	*routine(void *arg)
{
	t_ph	*ph;
	size_t	i;

	ph = (t_ph *)arg;
	i = ph->position;
	if (i % 2 == 0)
		usleep(10);
	while (1)
	{
		lock_fork(ph, i);
		ph_print(get_time() - ph->starting_time, ph, i, "is eating");
		usleep(ph->time_eat * 1000);
		ph->philo[i].total_eat++;
		unlock_fork(ph, i);
		usleep(10);
		if (ph->nbr_eat != 0 && ph->philo[i].total_eat == ph->nbr_eat)
			break ;
		ph_print(get_time() - ph->starting_time, ph, i, "is sleeping");
		usleep(ph->time_sleep * 1000);
		ph_print(get_time() - ph->starting_time, ph, i, "is thinking");
	}
	return (0);
}

void	create_routine(t_ph *ph)
{
	size_t	i;

	ph->position = 0;
	ph->starting_time = get_time();
	while (ph->position < ph->nbr_philo)
	{
		pthread_create(&ph->philo[ph->position].thread, 0, routine, (void *)ph);
		usleep(10);
		ph->position++;
	}
	i = 0;
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