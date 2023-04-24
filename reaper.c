/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:58:36 by yabad             #+#    #+#             */
/*   Updated: 2023/03/31 14:08:03 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define DONE -5

void	death(t_container *e, int i)
{
	pthread_mutex_lock(&e->rules.mutex[DIE]);
	e->rules.died = TRUE;
	if (!(e->rules.counter >= e->rules.ph_nb) && i != DONE)
		printf("%lld %d %s\n", get_time() - e->rules.t_start, \
			e->philo[i].id, "died");
	pthread_mutex_unlock(&e->rules.mutex[DIE]);
}

int	check_death(t_container *e)
{
	int			i;
	long long	time;

	i = 0;
	pthread_mutex_lock(&e->rules.mutex[COUNT_EAT]);
	if (e->rules.counter >= e->rules.ph_nb)
		death(e, DONE);
	pthread_mutex_unlock(&e->rules.mutex[COUNT_EAT]);
	while (i < e->rules.ph_nb)
	{
		pthread_mutex_lock(&e->rules.mutex[EAT]);
		time = e->philo[i].last_meal;
		pthread_mutex_unlock(&e->rules.mutex[EAT]);
		if (get_time() - time >= e->rules.t_die)
		{
			death(e, i);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	reaper(t_container *e)
{
	while (TRUE)
	{
		if (check_death(e))
			break ;
	}
}
