/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:02:38 by marilins          #+#    #+#             */
/*   Updated: 2026/06/05 10:12:47 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static int	philo_is_dead(t_philo *philo)
{
	long	last_meal;
	long	now;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time();
	if (now - last_meal >= philo->table->time_to_die)
		return (1);
	return (0);
}

static int	check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (philo_is_dead(&table->philo[i]))
		{
			set_stop(table);
			safe_print(&table->philo[i], "died");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_ate_enough(t_table *table)
{
	int	i;
	int	full;

	if (!table->has_optional)
		return (0);
	i = 0;
	full = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		if (table->philo[i].meals_eaten >= table->must_eat)
			full++;
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
		i++;
	}
	return (full == table->n_philo);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!is_stopped(table))
	{
		if (check_death(table))
			return (NULL);
		if (all_ate_enough(table))
		{
			set_stop(table);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
