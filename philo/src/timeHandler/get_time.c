/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:51:10 by misimon           #+#    #+#             */
/*   Updated: 2022/12/06 16:51:37 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

t_time	get_time(void)
{
	struct timeval	get_time;

	gettimeofday(&get_time, NULL);
	return (get_time.tv_sec * 1000 + get_time.tv_usec / 1000);
}
