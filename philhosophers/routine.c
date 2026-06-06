/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:26:20 by marilins          #+#    #+#             */
/*   Updated: 2026/06/05 10:48:12 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork");
	}
}

static void	drop_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
}

static int	eat(t_philo *philo)
{
	t_table	*table;
	int		is_full;

	table = philo->table;
	is_full = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	if (table->has_optional && philo->meals_eaten >= table->must_eat)
		is_full = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo, "is eating");
	smart_sleep(table, table->time_to_eat);
	return (is_full);
}

static void	one_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	safe_print(philo, "has taken a fork");
	smart_sleep(table, table->time_to_die);
	set_stop(table);
	safe_print(philo, "died");
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->n_philo == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_stopped(table))
	{
		take_forks(philo);
		if (eat(philo))
		{
			drop_forks(philo);
			break ;
		}
		drop_forks(philo);
		safe_print(philo, "is sleeping");
		smart_sleep(table, table->time_to_sleep);
		safe_print(philo, "is thinking");
	}
	return (NULL);
}
