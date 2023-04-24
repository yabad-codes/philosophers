/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:07:37 by yabad             #+#    #+#             */
/*   Updated: 2023/03/31 13:40:18 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_container *data, int ac, char **args)
{
	if (!initialize_args(data, ac, args))
		return (FAILURE);
	if (!initialize_mutexes(data))
		return (FAILURE);
	if (!initialize_philosophers(data))
	{
		free(data->rules.mutex);
		if (data->rules.forks)
			free(data->rules.forks);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_container	e;

	if (!is_args_valid(ac, av))
		return (FAILURE);
	if (!init(&e, ac, av))
		return (FAILURE);
	if (!start_sim(&e))
		end_sim(&e);
	return (SUCCESS);
}
