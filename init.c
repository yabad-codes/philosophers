/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:23:14 by yabad             #+#    #+#             */
/*   Updated: 2023/03/30 16:01:01 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define UNDEFINED -1

int	initialize_philosophers(t_container *e)
{
	int	i;

	e->rules.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
							e->rules.ph_nb);
	if (!e->rules.forks)
		return (FAILURE);
	e->philo = (t_philo *)malloc(sizeof(t_philo) * e->rules.ph_nb);
	if (!e->philo)
		return (FAILURE);
	i = -1;
	while (++i < e->rules.ph_nb)
		pthread_mutex_init(&e->rules.forks[i], NULL);
	i = -1;
	while (++i < e->rules.ph_nb)
	{
		e->philo[i].id = i + 1;
		e->philo[i].last_meal = e->rules.t_start;
		e->philo[i].lf = i;
		e->philo[i].rf = (i + 1) % e->rules.ph_nb;
		e->philo[i].rules = &e->rules;
		e->philo[i].ate = 0;
	}
	return (SUCCESS);
}

int	initialize_mutexes(t_container *e)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
								* NUM);
	if (!mutex)
		return (FAILURE);
	i = -1;
	while (++i < NUM)
		pthread_mutex_init(&mutex[i], NULL);
	e->rules.mutex = mutex;
	return (SUCCESS);
}

int	initialize_args(t_container *e, int ac, char **args)
{
	e->rules.ph_nb = (int)ft_long_atoi(args[1]);
	e->rules.t_die = (int)ft_long_atoi(args[2]);
	e->rules.t_eat = (int)ft_long_atoi(args[3]);
	e->rules.t_sleep = (int)ft_long_atoi(args[4]);
	e->rules.meal_nb = UNDEFINED;
	if (ac == 6)
		e->rules.meal_nb = (int)ft_long_atoi(args[5]);
	e->rules.died = FALSE;
	e->rules.counter = 0;
	e->rules.t_start = get_time();
	if (!e->rules.meal_nb || !e->rules.t_die \
		|| !e->rules.t_eat || !e->rules.t_sleep)
		return (FAILURE);
	return (SUCCESS);
}
