/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:44:23 by misimon           #+#    #+#             */
/*   Updated: 2022/11/28 21:05:51 by misimon          ###   ########.fr       */
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
void	*null_error(char *str);

#endif
