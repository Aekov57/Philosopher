/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:50:05 by misimon           #+#    #+#             */
/*   Updated: 2022/12/06 16:53:18 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_sleep(t_time limit, t_time starting)
{	
	t_time	time;

	time = get_time();
	while (time - starting < limit)
		time = get_time();
}
