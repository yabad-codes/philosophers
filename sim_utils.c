/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:51:26 by yabad             #+#    #+#             */
/*   Updated: 2023/03/30 17:50:54 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print_state(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->rules->mutex[PRINT]);
	if (!is_died(ph))
		printf("%lld %d %s\n", get_time() - ph->rules->t_start, ph->id, msg);
	pthread_mutex_unlock(&ph->rules->mutex[PRINT]);
}

int	is_died(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->mutex[DIE]);
	if (ph->rules->died)
	{
		pthread_mutex_unlock(&ph->rules->mutex[DIE]);
		return (TRUE);
	}
	pthread_mutex_unlock(&ph->rules->mutex[DIE]);
	return (FALSE);
}

void	ft_usleep(t_philo *ph, long long time)
{
	long long	t0;

	t0 = get_time();
	while (!is_died(ph))
	{
		if (get_time() - t0 >= time)
			break ;
		usleep(500);
	}
}
