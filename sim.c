/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:58:36 by yabad             #+#    #+#             */
/*   Updated: 2023/03/31 13:47:57 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sim(t_container *e)
{
	int	i;

	i = -1;
	while (++i < e->rules.ph_nb)
	{
		if (pthread_create(&e->philo[i].tid, NULL, philo_routine, &e->philo[i]))
			return (safe_exit("Error : Failed to create a thread\n"));
	}
	reaper(e);
	end_sim(e);
	return (SUCCESS);
}

void	end_sim(t_container *e)
{
	int	i;

	i = -1;
	while (++i < e->rules.ph_nb)
	{
		if (pthread_join(e->philo[i].tid, NULL))
			return ;
	}
	i = -1;
	while (++i < e->rules.ph_nb)
		pthread_mutex_destroy(&e->rules.forks[i]);
	i = -1;
	while (++i < NUM)
		pthread_mutex_destroy(&e->rules.mutex[i]);
	free(e->philo);
}
