/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:28:47 by yabad             #+#    #+#             */
/*   Updated: 2023/03/30 16:39:12 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define INT_MAX 2147483647

enum {
	HT = 9,
	CR = 13,
	SP = 32,
	ERR = 2
};

long int	ft_long_atoi(const char *str)
{
	int			sign;
	int			i;
	long int	n;

	sign = 1;
	i = 0;
	n = 0;
	while ((str[i] >= HT && str[i] <= CR) || str[i] == SP)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * sign);
}

int	is_allowed_chars(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	is_args_valid(int ac, char **av)
{
	long int	value;

	if (ac > 6)
		return (safe_exit("Error: Too many arguments.\n"));
	if (ac < 5)
		return (safe_exit("Error: Too few arguments.\n"));
	while (ac-- > 1)
	{
		if (!is_allowed_chars(av[ac]))
			return (safe_exit("Error: Invalid character.\n"));
		value = ft_long_atoi(av[ac]);
		if (ac == 1 && value == 0)
			return (safe_exit("Error: Number of philosophers can't be 0\n"));
		if (value > INT_MAX || value < 0)
			return (safe_exit("Error: Out of range.\n"));
	}
	return (SUCCESS);
}
