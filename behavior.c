/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:55 by yabad             #+#    #+#             */
/*   Updated: 2023/03/31 12:32:35 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->forks[ph->lf]);
	print_state(ph, "has taken a fork");
	pthread_mutex_lock(&ph->rules->forks[ph->rf]);
	print_state(ph, "has taken a fork");
	print_state(ph, "is eating");
	pthread_mutex_lock(&ph->rules->mutex[EAT]);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->rules->mutex[EAT]);
	ft_usleep(ph, ph->rules->t_eat);
	pthread_mutex_lock(&ph->rules->mutex[COUNT_EAT]);
	ph->ate++;
	if (ph->ate == ph->rules->meal_nb)
		ph->rules->counter++;
	pthread_mutex_unlock(&ph->rules->mutex[COUNT_EAT]);
}

void	release_forks(t_philo *ph)
{
	pthread_mutex_unlock(&ph->rules->forks[ph->lf]);
	pthread_mutex_unlock(&ph->rules->forks[ph->rf]);
}

void	sleep_and_think(t_philo *ph)
{
	print_state(ph, "is sleeping");
	ft_usleep(ph, ph->rules->t_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->rules->ph_nb == 1)
	{
		print_state(ph, "has taken a fork");
		ft_usleep(ph, ph->rules->t_die);
		print_state(ph, "died");
		return (NULL);
	}
	if (!(ph->id % 2))
		ft_usleep(ph, 5);
	while (!is_died(ph))
	{
		print_state(ph, "is thinking");
		eat(ph);
		release_forks(ph);
		sleep_and_think(ph);
	}
	return (NULL);
}
