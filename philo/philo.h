/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:44:23 by misimon           #+#    #+#             */
/*   Updated: 2022/12/06 17:51:18 by misimon          ###   ########.fr       */
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
}	t_philo;

typedef struct s_ph
{
	size_t			nbr_philo;
	t_philo			*philo;
	size_t			finish;
	size_t			position;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			nbr_eat;
	pthread_mutex_t	writing;
	t_time			starting_time;
	t_bool			error;
}	t_ph;

size_t	ft_atoi(const char *str);
t_ph	*init(int argc, char **argv);
int		write_error(char *str);
int		create_philo(t_ph *ph);
t_time	get_time(void);
void	*null_error(char *str);
void	ph_print(t_time time, t_ph *ph, size_t i, char *action);
void	ph_print_dead(t_time time, t_ph *ph, size_t i, char *action);
void	ft_sleep(t_time limit, t_time starting);
void	lock_fork(t_ph *ph, size_t i);
void	unlock_fork(t_ph *ph, size_t i);
t_bool	check_death(t_ph *ph, size_t i);

#endif
