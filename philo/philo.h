/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:44:23 by misimon           #+#    #+#             */
/*   Updated: 2022/12/16 09:24:47 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef long long	t_time;
typedef int			t_bool;

# define TRUE 1
# define FALSE 0

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	size_t			id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_time			last_eat;
	size_t			total_eat;
	struct s_ph		*rules;
}	t_philo;

typedef struct s_ph
{
	size_t			nbr_philo;
	t_philo			*philo;
	size_t			finish;
	size_t			all_eat;
	t_time			time_die;
	t_time			time_eat;
	t_time			time_sleep;
	size_t			nbr_eat;
	pthread_mutex_t	writing;
	pthread_mutex_t	check_eating;
	t_time			starting_time;
	t_bool			error;
}	t_ph;

size_t	ft_atoi(const char *str);
t_ph	*init(int argc, char **argv);
int		write_error(char *str);
int		create_philo(t_ph *ph);
t_time	get_time(void);
void	*null_error(char *str);
void	ph_print(t_philo *philo, char *action);
void	ph_print_dead(t_philo *philo, char *action);
void	ft_sleep(t_time limit);
void	lock_fork(t_philo *philo);
void	unlock_fork(t_philo *philo);
void	death_checker(t_ph *ph);

#endif
