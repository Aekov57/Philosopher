/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:50:05 by misimon           #+#    #+#             */
/*   Updated: 2022/12/12 08:12:17 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_sleep(t_time limit)
{	
	t_time	time;
	t_time	starting;

	starting = get_time();
	time = get_time();
	while (time - starting < limit)
		time = get_time();
}
