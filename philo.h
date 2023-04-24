/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:18:41 by yabad             #+#    #+#             */
/*   Updated: 2023/03/31 14:18:35 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum s_exit
{
	FAILURE,
	SUCCESS
}	t_exit;

typedef enum s_mutexes
{
	PRINT,
	DIE,
	EAT,
	COUNT_EAT,
	NUM
}	t_mutexes;

typedef struct s_rules
{
	int					ph_nb;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	long long			t_start;
	int					meal_nb;
	int					died;
	int					counter;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		*forks;
}	t_rules;

typedef struct s_philo
{
	int					id;
	long long			last_meal;
	int					ate;
	int					lf;
	int					rf;
	t_rules				*rules;
	pthread_t			tid;
}	t_philo;

typedef struct s_container
{
	t_rules	rules;
	t_philo	*philo;
}	t_container;

// Arguments checking
int			is_args_valid(int ac, char **av);

// Initialize Simulation ENV
int			initialize_args(t_container *e, int ac, char **args);
int			initialize_mutexes(t_container *e);
int			initialize_philosophers(t_container *e);

// Simulation
int			start_sim(t_container *e);
void		end_sim(t_container *e);

// Philos Behavior
void		*philo_routine(void *arg);

// Checking for simulation's end (REAPER)
void		reaper(t_container *e);

// Sim Util
void		ft_usleep(t_philo *ph, long long time);
void		print_state(t_philo *ph, char *msg);
long long	get_time(void);
int			is_died(t_philo *ph);

// Other Util
long int	ft_long_atoi(const char *str);
int			ft_isdigit(int c);
int			safe_exit(char *msg);
#endif